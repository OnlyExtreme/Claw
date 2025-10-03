/*
Copyright (c) 2025 Sparx.
See LICENSE for details.
*/

#include "app/app.hpp"
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>

using namespace ftxui;

int main() {
	App app;

	auto screen = ScreenInteractive::Fullscreen();

	auto renderer = Renderer([&] {
		return app.Render();
	});

	auto exit_loop = screen.ExitLoopClosure();

	auto component = CatchEvent(renderer, [&](Event event) {
		if (event == Event::Character('q')) {
			exit_loop();
			return true;
		}
		if (event.is_character()) {
			app.HandleInput(event.character()[0]);
			return true;
		}
		return false;
	});

	screen.Loop(component);
}