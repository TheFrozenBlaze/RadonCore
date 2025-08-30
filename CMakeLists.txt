cmake_minimum_required(VERSION 3.16)
project(RadonApp VERSION 0.1 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Sources
add_executable(RadonApp
    src/radon.cpp
    src/glad.c
    src/shaperenderer.cpp
    src/window.cpp
    src/whileaction.cpp
    src/fileutils.cpp
    external/imgui.cpp
    external/imgui_draw.cpp
    external/imgui_tables.cpp
    external/imgui_widgets.cpp
    external/imgui_impl_glfw.cpp
    external/imgui_impl_opengl3.cpp
    external/tinyfiledialogs.c
)

target_include_directories(RadonApp PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/external
)

# Use static GLFW
target_compile_definitions(RadonApp PRIVATE GLFW_STATIC)

# Link GLFW (static) and OpenGL
target_link_libraries(RadonApp PRIVATE
    ${CMAKE_SOURCE_DIR}/lib/libglfw3.a # MinGW static lib
    opengl32
)