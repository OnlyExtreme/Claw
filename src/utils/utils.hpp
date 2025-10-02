#pragma once
#include <string>
#include <Windows.h>

std::string to_utf8(const std::wstring& w);
std::wstring get_parent(const std::wstring& path);