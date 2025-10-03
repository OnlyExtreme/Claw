/*
Copyright (c) 2025 Sparx
See LICENSE for details.
*/

#include "filepane.hpp"
#include "../core/file_ops.hpp"
#include "../utils/utils.hpp"
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/screen/string.hpp>
#include <ftxui/screen/color.hpp>

FilePane::FilePane(const std::wstring& start_path) {
	current_path_ = start_path;
	entries_ = this->fs_.list_directory(current_path_);
	selected_index_ = 0;
}

void FilePane::set_directory(const std::wstring& path) {
	current_path_ = path;
	entries_ = fs_.list_directory(current_path_);
	selected_index_ = 0;
}

const std::wstring& FilePane::current_directory() const {
	return current_path_;
}

void FilePane::next_file() {
	if (selected_index_ < fs_.list_directory(current_path_).size() - 1)
		selected_index_ += 1;
	return;
}

void FilePane::previous_file() {
	if (selected_index_ > 1)
		selected_index_ -= 1;
	return;
}

void FilePane::enter_selected() {
	FileEntry selected_entry = fs_.list_directory(current_path_)[selected_index_];
	if (!selected_entry.is_dir)
		return;
	std::wstring new_path = current_path_ + selected_entry.name + L"\\";
	set_directory(new_path);
	return;
}

void FilePane::enter_parent() {
	std::wstring parent = get_parent(current_path_);
	set_directory(parent);
	return;
}

int FilePane::selected_index() const {
	return selected_index_;
}

ftxui::Element FilePane::Render() {
	std::vector<ftxui::Element> items;
	for (size_t i = 0; i < entries_.size(); i++) {
		auto style = (i == selected_index_) ? ftxui::inverted : ftxui::nothing;
		auto color = entries_[i].is_dir ? ftxui::color(ftxui::Color::Blue) : ftxui::color(ftxui::Color::White);
		items.push_back(ftxui::text(entries_[i].name) | style | color);
	}
	return vbox(items);
}