/*
Copyright (c) 2025 Sparx
See LICENSE for details.
*/

#include "filepane.hpp"
#include "../core/file_ops.hpp"
#include "../utils/utils.hpp"

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