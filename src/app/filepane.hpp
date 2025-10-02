#include "../core/file_ops.hpp"

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

private:
	std::wstring current_path_;
	std::vector<FileEntry> entries_;
	int selected_index_;

	FileSystem fs_;
};