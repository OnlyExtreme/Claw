#include "filepane.hpp"
#include "app.hpp"
#include "../ui/ui.hpp"
#include <string>


/*
* Constructor of Class App.
* Currently forcing initial paths to C:\ and D:\, might change later.
*/
App::App() : left_pane_(L"C:\\"), right_pane_(L"D:\\") {
	left_active_ = true;
	status_ = STATUS::StateNormal;
}

/*
* Invoke the render function for the whole application implemented in ui.cpp
*/
ftxui::Element App::Render() {
	return render_app(*this);
}

/*
* Handle (character?) inputs.
* Consider including special inputs and events.
*/
void App::HandleInput(char key) {
	if (status_ == STATUS::StateSearch) {
		FilePane& active = left_active_ ? left_pane_ : right_pane_;
		active.locate_with_character(key);
		status_ = STATUS::StateNormal;
		return;
	}


	if (status_ == STATUS::StateNormal) {
		
		if (key == 'f') enter_mode(STATUS::StateSearch);

		if (key == 'H') left_active_ = true;
		if (key == 'L') left_active_ = false;

		FilePane& active = left_active_ ? left_pane_ : right_pane_;
		if (key == 'j') active.next_file();
		if (key == 'k') active.previous_file();
		if (key == 'd') active.down_half_screen();
		if (key == 'u') active.up_half_screen();
		if (key == 'l')	active.enter_selected();
		if (key == 'h') active.enter_parent();
	}
}

FilePane App::left_pane() const {
	return left_pane_;
}

FilePane App::right_pane() const {
	return right_pane_;
}

bool App::left_active() const {
	return left_active_;
}

STATUS App::status() const {
	return status_;
}

/*
* Deals with mode changing issues.
*/
void App::enter_mode(STATUS target_status) {
	if (status_ == target_status)
		return;
	status_ = target_status;
	return;
}