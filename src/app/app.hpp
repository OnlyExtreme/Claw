/*
Copyright (c) 2025 Sparx.
See LICENSE for details.
*/

#include "filepane.hpp"
#include <string>

/*
Handles the whole application, including global status and inputs.
*/
class App {
public:
	App()
		: left_pane_(L"C:\\"), right_pane_(L"D:\\") {};

	ftxui::Element Render();
	void HandleInput(char key);

private:
	FilePane left_pane_;
	FilePane right_pane_;
	bool left_active_;
};