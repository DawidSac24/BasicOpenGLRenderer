cmake_minimum_required(VERSION 3.21)

# --- Vcpkg Integration ---
# This must be done BEFORE the project() call to correctly set up the environment.
if(NOT CMAKE_TOOLCHAIN_FILE AND DEFINED ENV{VCPKG_ROOT})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
endif()

project(OpenGLRenderer VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# --- Build Options ---
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(TREAT_WARNINGS_AS_ERRORS "Treat warnings as errors" ON)

# --- Compiler Flags ---
if(MSVC)
    if(TREAT_WARNINGS_AS_ERRORS)
        add_compile_options(/W4 /WX /permissive- /utf-8)
    else()
        add_compile_options(/W4 /permissive- /utf-8)
    endif()
else()
    if(TREAT_WARNINGS_AS_ERRORS)
        add_compile_options(-Wall -Wextra -Wpedantic -Werror)
    else()
        add_compile_options(-Wall -Wextra -Wpedantic)
    endif()
endif()

# --- Output Directories ---
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# --- Enter Source Directory ---
add_subdirectory(src)

# --- Installation ---
install(DIRECTORY res/ DESTINATION share/OpenGLRenderer/res)
