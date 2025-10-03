/*
Copyright (c) 2025 Sparx.
See LICENSE for details.
*/

#include "ui.hpp"
#include "../utils/utils.hpp"
#include "../app/filepane.hpp"
#include "../app/app.hpp"
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/screen/string.hpp>
#include <ftxui/screen/color.hpp>

using namespace ftxui;

Element render_filepane(const FilePane& pane) {
	std::vector<Element> items;
	for (size_t i = 0; i < pane.entries().size(); i++) {
		auto style = (i == pane.selected_index()) ? inverted : nothing;
		auto item_color = pane.entries()[i].is_dir ? color(Color::Blue) : color(Color::White);
		items.push_back(text(pane.entries()[i].name) | style | item_color);
	}
	return vbox(items);
}

Element render_app(const App& app) {
	auto left = app.left_pane().Render();
	auto right = app.right_pane().Render();
	auto left_active = app.left_active();

	left = border(left) | (left_active ? color(Color::Green) : color(Color::White));
	right = border(right) | (left_active ? color(Color::White) : color(Color::Green));
	
	left = vbox({
		text(app.left_pane().current_directory()),
		left,
	});
	right = vbox({
		text(app.right_pane().current_directory()),
		right,
	});

	return hbox({
		left | size(WIDTH, EQUAL, Terminal::Size().dimx / 2),
		right | size(WIDTH, EQUAL, Terminal::Size().dimx / 2),
	});
}