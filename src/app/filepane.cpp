/*
Copyright (c) 2025 Sparx
See LICENSE for details.
*/

#include "filepane.hpp"
#include "../core/file_ops.hpp"
#include "../utils/utils.hpp"
#include "../ui/ui.hpp"
#include <algorithm>
#include <ftxui/dom/elements.hpp>

FilePane::FilePane(const std::wstring& start_path) {
	current_path_ = start_path;
	entries_ = this->fs_.list_directory(current_path_);
	selected_index_ = 0;
	list_offset_ = 0;
}

// Set the new directory and initialize index and offset.
void FilePane::set_directory(const std::wstring& path, int index, int offset) {
	current_path_ = path;
	entries_ = fs_.list_directory(current_path_);
	if (index >= 0 && index < entries_.size())
		selected_index_ = index;
	else
		selected_index_ = 0;
	if (offset >= 0 && offset < entries_.size())
		list_offset_ = offset;
	else
		list_offset_ = 0;
}

const std::wstring& FilePane::current_directory() const {
	return current_path_;
}

// Calculates offset after a jump or change of directory.
int FilePane::reset_offset(int index) {
	if (entries_.size() <= ftxui::Terminal::Size().dimy - 4)
		return 0;
	int offset = 0;
	if (index > ftxui::Terminal::Size().dimy / 2 - 2)
		offset = index - ftxui::Terminal::Size().dimy / 2 + 2;
	if (index > entries_.size() - ftxui::Terminal::Size().dimy / 2 + 2)
		offset = entries_.size() - ftxui::Terminal::Size().dimy + 4;
	return offset;
}

// Select the next file, considering index and offset.
void FilePane::next_file() {
	if (selected_index_ < fs_.list_directory(current_path_).size() - 1)
		selected_index_ += 1;
	if (selected_index_ > list_offset_ + ftxui::Terminal::Size().dimy - 4)
		list_offset_ += 1;
	return;
}

// Select the previous file, considering index and offset.
void FilePane::previous_file() {
	if (selected_index_ > 0)
		selected_index_ -= 1;
	if (selected_index_ < list_offset_)
		list_offset_ -= 1;
	return;
}

// Scroll down half screen, considering index and offset.
void FilePane::down_half_screen() {
	int half_screen = ftxui::Terminal::Size().dimy / 2 - 2;
	selected_index_ = min(entries_.size() - 1, selected_index_ + half_screen);
	if (selected_index_ > list_offset_ + ftxui::Terminal::Size().dimy - 4)
		list_offset_ = selected_index_ - ftxui::Terminal::Size().dimy + 4;
	return;
}

// Scroll up half screen, considering index and offset.
void FilePane::up_half_screen() {
	int half_screen = ftxui::Terminal::Size().dimy / 2 - 2;
	selected_index_ = max(0, selected_index_ - half_screen);
	if (selected_index_ < list_offset_)
		list_offset_ = selected_index_;
	return;
}

// Enter the selected entry if it is a directory, open the file with default app otherwise.
void FilePane::enter_selected() {
	FileEntry selected_entry = fs_.list_directory(current_path_)[selected_index_];
	if (!selected_entry.is_dir) {
		fs_.open_file(current_path_ + selected_entry.name);
		return;
	}
	std::wstring new_path = current_path_ + selected_entry.name + L"\\";
	set_directory(new_path, 0, 0);
	return;
}

// Enter the parent directory and reset the index and offset.
void FilePane::enter_parent() {
	std::wstring parent = get_parent(current_path_);
	std::wstring file_name = current_path_.substr(current_path_.rfind(parent)+parent.size(), current_path_.size() - parent.size() - 1);
	auto entries = fs_.list_directory(parent);
	int index = get_index(entries, file_name);
	int offset = reset_offset(index);
	set_directory(parent, index, offset);
	return;
}

// For "f+<ch>" search, locate the first file starting with character <ch>. Case insensitive.
void FilePane::locate_with_character(wchar_t ch) {
	for (size_t i = 0; i < entries_.size(); i++) {
		if (towlower(entries_[i].name[0]) == towlower(ch)) {
			selected_index_ = i;
			list_offset_ = reset_offset(i);
			return;
		}
	}
	return;
}

int FilePane::selected_index() const {
	return selected_index_;
}

int FilePane::list_offset() const {
	return list_offset_;
}

ftxui::Element FilePane::Render() {
	return render_filepane(*this);
}

const std::vector<FileEntry>& FilePane::entries() const {
	return entries_;
}