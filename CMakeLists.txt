cmake_minimum_required(VERSION 3.16)
project(claw LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG v6.1.9
)
FetchContent_MakeAvailable(ftxui)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(claw
	src/main.cpp
	"src/core/file_ops.cpp"
	"src/ui/ui.cpp"
	"src/utils/utils.cpp"
 "src/app/filepane.cpp" "src/app/app.cpp")

target_link_libraries(claw PRIVATE
	ftxui::component
	ftxui::dom
	ftxui::screen
)

if(WIN32)
	target_link_libraries(claw PRIVATE user32 kernel32)
endif()