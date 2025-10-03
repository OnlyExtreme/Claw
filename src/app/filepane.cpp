/*
Copyright (c) 2025 Sparx
See LICENSE for details.
*/

#include "filepane.hpp"
#include "../core/file_ops.hpp"
#include "../utils/utils.hpp"
#include "../ui/ui.hpp"
#include <algorithm>
#include <iostream>

FilePane::FilePane(const std::wstring& start_path) {
	current_path_ = start_path;
	entries_ = this->fs_.list_directory(current_path_);
	selected_index_ = 0;
}

void FilePane::set_directory(const std::wstring& path, int index) {
	current_path_ = path;
	entries_ = fs_.list_directory(current_path_);
	if (index >= 0 && index < entries_.size())
		selected_index_ = index;
	else
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
	if (selected_index_ > 0)
		selected_index_ -= 1;
	return;
}

void FilePane::enter_selected() {
	FileEntry selected_entry = fs_.list_directory(current_path_)[selected_index_];
	if (!selected_entry.is_dir)
		return;
	std::wstring new_path = current_path_ + selected_entry.name + L"\\";
	set_directory(new_path, 0);
	return;
}

void FilePane::enter_parent() {
	std::wstring parent = get_parent(current_path_);
	std::wstring file_name = current_path_.substr(current_path_.rfind(parent)+parent.size(), current_path_.size() - parent.size() - 1);
	auto entries = fs_.list_directory(parent);
	set_directory(parent, get_index(entries, file_name));
	return;
}

int FilePane::selected_index() const {
	return selected_index_;
}

ftxui::Element FilePane::Render() {
	return render_filepane(*this);
}

const std::vector<FileEntry>& FilePane::entries() const {
	return entries_;
}