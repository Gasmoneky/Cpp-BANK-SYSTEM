cmake_minimum_required(VERSION 3.10)
project(MMUST-FRONTEND-BANK)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
cmake_policy(SET CMP0072 NEW)

# 1. Find System Dependencies
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(OpenSSL REQUIRED) # Crucial for HTTPS calls to your Droplet
find_package(Threads REQUIRED) # Needed for httplib's networking

# 2. Define Third-Party Paths
set(THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party)
set(IMGUI_DIR ${THIRD_PARTY_DIR}/imgui)
set(HTTPLIB_DIR ${THIRD_PARTY_DIR}/httplib)
set(JSON_DIR ${THIRD_PARTY_DIR}/json)

# 3. Include Directories (Where the .h and .hpp files are)
include_directories(
    include
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
    ${HTTPLIB_DIR}    # Point this to where httplib.h is
    ${JSON_DIR}/include # nlohmann/json usually puts headers in an 'include' subfolder
)

# 4. Source Files (Including your new Auth logic)
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

# Recursively find all your .cpp files in src (including src/core/auth.cpp)
file(GLOB_RECURSE PROJECT_SOURCES "src/*.cpp")

# 5. Create the Executable
add_executable(${PROJECT_NAME} 
    ${PROJECT_SOURCES} 
    ${IMGUI_SOURCES}
    src/ui/authui.cpp
    src/service/authservice.cpp
    include/service/authservice.h
)

# 6. Link the "Muscles" (Libraries)
target_link_libraries(${PROJECT_NAME} 
    glfw 
    OpenGL::GL 
    OpenSSL::SSL 
    OpenSSL::Crypto
    Threads::Threads
    ${CMAKE_DL_LIBS}
)
# Forces the compiler to include line numbers and variable names in the binary
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

# Explicitly add -g for GCC/Clang if in Debug mode
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")