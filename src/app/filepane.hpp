/*
Copyright (c) 2025 Sparx.
See LICENSE for details.
*/

#include "../core/file_ops.hpp"
#include <ftxui/dom/elements.hpp>

/*
FilePane class, the data structure for a single tab of the file manager.
Consists of a FileSystem and the status.
*/
class FilePane {
public:
	FilePane(const std::wstring& start_path);

	void set_directory(const std::wstring& path);
	const std::wstring& current_directory() const;

	void next_file();
	void previous_file();
	void enter_selected();
	void enter_parent();

	int selected_index() const;
	const std::vector<FileEntry>& entries() const;

	ftxui::Element Render();

private:
	std::wstring current_path_;
	std::vector<FileEntry> entries_;
	int selected_index_;

	FileSystem fs_;
};