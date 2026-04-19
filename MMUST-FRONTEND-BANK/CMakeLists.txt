cmake_minimum_required(VERSION 3.10)
project(MMUST-FRONTEND-BANK)

# 1. Use C++17 for modern features
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 2. Fix the OpenGL policy warning for Fedora
cmake_policy(SET CMP0072 NEW)

# 3. Find System Dependencies (GPU/Windowing)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

# 4. Define ImGui Paths (Based on your 'third_party' folder)
set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/imgui)

# 5. Tell the compiler where to look for headers (.h files)
include_directories(
    include 
    ${IMGUI_DIR} 
    ${IMGUI_DIR}/backends
)

# 6. Manually collect ImGui source files
# We compile these directly into your app
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

# 7. Collect your own source files
# I'm explicitly adding main.cpp and recursively finding others in src
file(GLOB_RECURSE PROJECT_SOURCES "src/*.cpp")

# 8. Create the Executable
add_executable(${PROJECT_NAME} 
    src/main.cpp 
    ${PROJECT_SOURCES} 
    ${IMGUI_SOURCES}
)

# 9. Link everything together (The Handshake)
target_link_libraries(${PROJECT_NAME} 
    glfw 
    OpenGL::GL 
    ${CMAKE_DL_LIBS}
)