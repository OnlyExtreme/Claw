#include "filepane.hpp"
#include "app.hpp"
#include "../ui/ui.hpp"
#include <string>


App::App() : left_pane_(L"C:\\"), right_pane_(L"D:\\") {
	left_active_ = true;
}

ftxui::Element App::Render() {
	return render_app(*this);
}

void App::HandleInput(char key) {
	if (key == 'H') left_active_ = true;
	if (key == 'L') left_active_ = false;
	
	FilePane& active = left_active_ ? left_pane_ : right_pane_;
	if (key == 'j') active.next_file();
	if (key == 'k') active.previous_file();
	if (key == 'l')	active.enter_selected();
	if (key == 'h') active.enter_parent();
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