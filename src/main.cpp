/*
Copyright (c) 2025 Sparx.
See LICENSE for details.
*/

#include "core/file_ops.hpp"
#include "ui/ui.hpp"
#include "utils/utils.hpp"

int main() {
	FileSystem sys;
	auto files = sys.list_directory(L"C:\\");
	run_ui(files);
	return 0;
}