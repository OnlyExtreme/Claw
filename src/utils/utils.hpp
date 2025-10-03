/*
Copyright (c) 2025 Sparx.
See LICENSE for details.
*/

#pragma once
#include "../core/file_ops.hpp"
#include <string>
#include <vector>
#include <Windows.h>

// converts wstring to utf8 string
std::string to_utf8(const std::wstring& w);

// get the parent directory of given path. Special cases handled here.
std::wstring get_parent(const std::wstring& path);

// get the index of given file name
int get_index(std::vector<FileEntry>& files, const std::wstring& name);