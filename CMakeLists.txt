cmake_minimum_required(VERSION 3.21)

# --- Vcpkg Integration ---
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
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# --- Compiler Flags ---
add_library(project_warnings INTERFACE)

if(MSVC)
    target_compile_options(project_warnings INTERFACE 
        /W4 /permissive- /utf-8
        $<$<BOOL:${TREAT_WARNINGS_AS_ERRORS}>:/WX>
    )
else()
    target_compile_options(project_warnings INTERFACE 
        -Wall -Wextra -Wpedantic
        $<$<BOOL:${TREAT_WARNINGS_AS_ERRORS}>:-Werror>
    )
endif()

# --- Output Directories ---
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# --- Enter Source Directory ---
add_subdirectory(src)

# --- Installation ---
install(DIRECTORY res/ DESTINATION share/OpenGLRenderer/res)
