cmake_minimum_required(VERSION 3.16)

project(OpenGLRenderer VERSION 1.0)

# --- Settings ---
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# --- Dependencies ---
include(dependencies.cmake)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

# --- Build ImGui (Library) ---
add_library(imgui STATIC
    "${imgui_SOURCE_DIR}/imgui.cpp"
    "${imgui_SOURCE_DIR}/imgui_draw.cpp"
    "${imgui_SOURCE_DIR}/imgui_tables.cpp"
    "${imgui_SOURCE_DIR}/imgui_widgets.cpp"
    "${imgui_SOURCE_DIR}/imgui_demo.cpp"
    "${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp"
    "${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp"
)

target_include_directories(imgui PUBLIC 
    "${imgui_SOURCE_DIR}" 
    "${imgui_SOURCE_DIR}/backends"
)

target_link_libraries(imgui PUBLIC glfw GLEW::glew OpenGL::GL)

# --- Build STB Image (Library) ---
add_library(stb_image STATIC "vendor/stb_image/stb_image.cpp")
target_include_directories(stb_image PUBLIC "vendor/stb_image")

# --- Enter Source Directory ---
add_subdirectory(src)
