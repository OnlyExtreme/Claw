#include "file_ops.hpp"
#include <iostream>

int main() {
	FileSystem sys;
	auto files = sys.list_directory(L"C:\\");
	for (auto entry : files) {
		std::wcout << entry.name << std::endl;
	}
	return 0;
}