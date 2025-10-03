#include "filepane.hpp"
#include "app.hpp"
#include <string>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/screen/string.hpp>
#include <ftxui/screen/color.hpp>

App::App() : left_pane_(L"C:\\"), right_pane_(L"D:\\") {
	left_active_ = true;
}

ftxui::Element App::Render() {
	auto left = left_pane_.Render();
	auto right = right_pane_.Render();

	if (left_active_)
		left = ftxui::border(left) | ftxui::color(ftxui::Color::Green);
	else
		right = ftxui::border(right) | ftxui::color(ftxui::Color::Green);

	return ftxui::hbox({
		left | ftxui::flex,
		right | ftxui::flex,
		});
}

void App::HandleInput(char key) {
	if (key == 'H') left_active_ = true;
	if (key == 'L') left_active_ = false;
	
	FilePane& active = left_active_ ? left_pane_ : right_pane_;
	if (key == 'j') active.next_file();
	if (key == 'k') active.previous_file();
	if (key == 'h')	active.enter_selected();
	if (key == 'l') active.enter_parent();
}

