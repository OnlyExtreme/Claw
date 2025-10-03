/*
Copyright (c) 2025 Sparx.
See LICENSE for details.
*/

#pragma once
#include "../core/file_ops.hpp"
#include "../app/filepane.hpp"
#include "../app/app.hpp"
#include <vector>

ftxui::Element render_filepane(const FilePane& pane);
ftxui::Element render_app(const App& app);