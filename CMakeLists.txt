cmake_minimum_required(VERSION 3.16)
project(OpenGLGameEngine VERSION 1.0)

# --- Settings ---
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# --- Enter Source Directory ---
add_subdirectory(src)
