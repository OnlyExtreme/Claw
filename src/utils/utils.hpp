/*
Copyright (c) 2025 Sparx.
See LICENSE for details.
*/

#pragma once
#include <string>
#include <Windows.h>

// converts wstring to utf8 string
std::string to_utf8(const std::wstring& w);

// get the parent directory of given path. Special cases handled here.
std::wstring get_parent(const std::wstring& path);