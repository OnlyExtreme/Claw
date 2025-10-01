#pragma once
#include <string>
#include <vector>

struct FileEntry {
	std::wstring name;
	bool is_dir;
	uint64_t size;
};

class FileSystem {
public:
	std::vector<FileEntry> list_directory(const std::wstring& path);
	bool copy(const std::wstring& src, const std::wstring& dst);
	bool move(const std::wstring& src, const std::wstring& dst);
	bool remove(const std::wstring& path);
};