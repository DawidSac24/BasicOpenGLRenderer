add_library(Engine STATIC "")
add_library(OpenGLRenderer::Engine ALIAS Engine)
add_executable(OpenGLRenderer "")

target_compile_definitions(Engine PUBLIC PROJECT_ROOT="${CMAKE_SOURCE_DIR}")
target_include_directories(Engine
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(nfd CONFIG REQUIRED)
find_package(Stb REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

target_link_libraries(Engine PUBLIC
    glm::glm
    OpenGL::GL
    GLEW::GLEW
    glfw
    imgui::imgui
    spdlog::spdlog
    fmt::fmt
    PRIVATE
    nfd::nfd
    assimp::assimp
    project_warnings
)

add_subdirectory(Engine)
add_subdirectory(Application)

target_link_libraries(OpenGLRenderer PRIVATE Engine project_warnings)

add_custom_command(TARGET OpenGLRenderer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/res ${CMAKE_BINARY_DIR}/bin/res
    COMMENT "Copying resources to build directory"
)

install(TARGETS OpenGLRenderer Engine
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
