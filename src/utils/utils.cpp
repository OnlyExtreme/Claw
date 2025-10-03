/*
Copyright (c) 2025 Sparx.
See LICENSE for details.
*/

#include "utils.hpp"

std::string to_utf8(const std::wstring& w) {
	if (w.empty())
		return {};
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, w.c_str(), (int)w.size(), NULL, 0, NULL, NULL);

	std::string result(size_needed, 0);
	WideCharToMultiByte(CP_UTF8, 0, w.c_str(), (int)w.size(), result.data(), size_needed, NULL, NULL);
	return result;
}

std::wstring get_parent(const std::wstring& path) {
	std::wstring parent;
	size_t pos = (path.substr(0, path.length() - 1).find_last_of(L"\\"));
	if (pos == std::wstring::npos)
		return path;
	return path.substr(0, pos+1);
}