/*
Copyright (c) 2025 Sparx.
See LICENSE for details.
*/

#pragma once
#include <string>
#include <vector>

/*
FileEntry for storing the information of a single file entry.
*/
struct FileEntry {
	std::wstring name;
	bool is_dir;
	int64_t size;
};

/*
FileSystem for functions directly related to file operations, implemented with Win32 API.
*/
class FileSystem {
public:
	std::vector<FileEntry> list_directory(const std::wstring& path);
	bool copy(const std::wstring& src, const std::wstring& dst);
	bool move(const std::wstring& src, const std::wstring& dst);
	bool remove(const std::wstring& path);
};