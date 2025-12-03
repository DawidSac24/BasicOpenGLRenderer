cmake_minimum_required(VERSION 3.15)

project(OpenGLRenderer VERSION 1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(stb_image STATIC "vendor/stb_image/stb_image.cpp")
target_include_directories(stb_image PUBLIC "vendor/stb_image")

include(dependencies.cmake)

find_package(glfw3 3.4 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")

add_executable(${PROJECT_NAME} 
    ${SOURCES}
)

target_include_directories(${PROJECT_NAME} PRIVATE 
 src 
 "vendor/stb_image"
)


target_link_libraries(${PROJECT_NAME} PRIVATE 
  glfw
  OpenGL::GL
  GLEW::glew
  stb_image
)
