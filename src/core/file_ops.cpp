/*
Copyright (c) 2025 Sparx.
See LICENSE for details.
*/

#include "file_ops.hpp"
#include <Windows.h>

std::vector<FileEntry> FileSystem::list_directory(const std::wstring& path) {
	std::vector<FileEntry> result;

	std::wstring search_path = path + L"\\*";
	WIN32_FIND_DATAW ffd;
	HANDLE hFind = INVALID_HANDLE_VALUE;

	hFind = FindFirstFileW(search_path.c_str(), &ffd);

	if (INVALID_HANDLE_VALUE == hFind)
		return result;
	
	do {
		if (wcscmp(ffd.cFileName, L".") == 0 || wcscmp(ffd.cFileName, L"..") == 0)
			continue;

		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			result.push_back({ ffd.cFileName, true });
		else {
			LARGE_INTEGER filesize;
			filesize.LowPart = ffd.nFileSizeLow;
			filesize.HighPart = ffd.nFileSizeHigh;
			result.push_back({ ffd.cFileName, false, filesize.QuadPart });
		}
	} while (FindNextFileW(hFind, &ffd) != 0);

	FindClose(hFind);
	return result;
}