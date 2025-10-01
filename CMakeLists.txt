cmake_minimum_required(VERSION 3.16)
project(claw LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(claw
	src/main.cpp
	src/file_ops.cpp
)

if(WIN32)
	target_link_libraries(claw PRIVATE user32 kernel32)
endif()