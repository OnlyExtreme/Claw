/*
Copyright (c) 2025 Sparx.
See LICENSE for details.
*/

#pragma once
#include "filepane.hpp"
#include <string>

/*
* The enum for global states of the application.
*/
enum STATUS { StateNormal, StateSearch, StateCommand };

/*
* Handles the whole application, including global status and inputs.
*/
class App {
public:
	App();

	ftxui::Element Render();
	void HandleInput(char key);

	FilePane left_pane() const;
	FilePane right_pane() const;
	bool left_active() const;
	STATUS status() const;

	void enter_mode(STATUS target_status);

private:
	FilePane left_pane_;
	FilePane right_pane_;
	bool left_active_ = true;
	STATUS status_ = STATUS::StateNormal;
};