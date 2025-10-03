/*
Copyright (c) 2025 Sparx.
See LICENSE for details.
*/

#pragma once
#include "filepane.hpp"
#include <string>

/*
Handles the whole application, including global status and inputs.
*/
class App {
public:
	App();

	ftxui::Element Render();
	void HandleInput(char key);

	FilePane left_pane() const;
	FilePane right_pane() const;
	bool left_active() const;

private:
	FilePane left_pane_;
	FilePane right_pane_;
	bool left_active_ = true;
};