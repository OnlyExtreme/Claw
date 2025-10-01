#include "file_ops.hpp"
#include "ui.hpp"
#include "utils.hpp"
#include <iostream>

int main() {
	FileSystem sys;
	auto files = sys.list_directory(L"C:\\");
	run_ui(files);
	return 0;
}