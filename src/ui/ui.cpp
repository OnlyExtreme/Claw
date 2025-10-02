#include "ui.hpp"
#include "../utils/utils.hpp"
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/screen/string.hpp>
#include <ftxui/screen/color.hpp>

using namespace ftxui;

void run_ui(std::vector<FileEntry>& files) {
	Elements entries;
	for (auto& f : files) {
		std::wstring name = f.name;
		if (!f.is_dir)
			name += L"     " + (std::to_wstring(f.size)) + L" bytes";
		entries.push_back(
			text(name) | (f.is_dir ? color(Color::Blue) : color(Color::White))
		);
	}

	auto doc = vbox({
		text("Claw") | bold | color(Color::Green),
		separator(),
		vbox(std::move(entries))
	});

	auto screen = Screen::Create(Dimension::Full(), Dimension::Full());
	Render(screen, doc);
	screen.Print();
}