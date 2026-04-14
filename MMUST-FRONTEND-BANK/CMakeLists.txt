cmake_minimum_required(VERSION 3.10)
project(MMUST-FRONTEND-BANK)

set(CMAKE_CXX_STANDARD 17)

# Tell CMake where to look for your headers
include_directories(include)

# Find necessary packages
find_package(glfw3 REQUIRED)
find_package(imgui REQUIRED)
find_package(OpenGL REQUIRED)

# Collect all your source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(MMUST-FRONTEND-BANK ${SOURCES})

# Link the libraries
target_link_libraries(MMUST-FRONTEND-BANK imgui::imgui glfw OpenGL::GL)
