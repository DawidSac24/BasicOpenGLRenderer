set(ENGINE_SOURCES
    Engine/Core/AssetManager.cpp
    Engine/Core/AssetManager.h
    Engine/Core/FileSystem.h
    Engine/Core/keyCodes.h
    Engine/Core/Layer.h
    Engine/Core/LayerStack.cpp
    Engine/Core/LayerStack.h
    Engine/Core/Log.cpp
    Engine/Core/Log.h
    Engine/Core/UUID.cpp
    Engine/Core/UUID.h
    Engine/Editor/EditorLayer.cpp
    Engine/Editor/EditorLayer.h
    Engine/Editor/EditorPanels.h
    Engine/Events/ApplicationEvents.h
    Engine/Events/Event.h
    Engine/Events/InputEvents.h
    Engine/Events/WindowEvents.h
    Engine/ImGui/ImGuiImpl.cpp
    Engine/ImGui/ImGuiImpl.h
    Engine/ImGui/MenuItems.h
    Engine/Math/Transform.h
    Engine/Platform/OpenGL/Application.cpp
    Engine/Platform/OpenGL/Application.h
    Engine/Platform/OpenGL/Debug.h
    Engine/Platform/OpenGL/Window.cpp
    Engine/Platform/OpenGL/Window.h
    Engine/Renderer/buffers/IndexBuffer.cpp
    Engine/Renderer/buffers/IndexBuffer.h
    Engine/Renderer/buffers/VertexArray.cpp
    Engine/Renderer/buffers/VertexArray.h
    Engine/Renderer/buffers/VertexBuffer.cpp
    Engine/Renderer/buffers/VertexBuffer.h
    Engine/Renderer/buffers/VertexBufferLayout.cpp
    Engine/Renderer/buffers/VertexBufferLayout.h
    Engine/Renderer/Material.h
    Engine/Renderer/Mesh.cpp
    Engine/Renderer/MeshFactory.cpp
    Engine/Renderer/MeshFactory.h
    Engine/Renderer/Mesh.h
    Engine/Renderer/Renderer.cpp
    Engine/Renderer/Renderer.h
    Engine/Renderer/Shader.cpp
    Engine/Renderer/Shader.h
    Engine/Renderer/Texture.cpp
    Engine/Renderer/Texture.h
    Engine/Scene/Components/CameraComponent.h
    Engine/Scene/Components/Component.h
    Engine/Scene/Components/MeshRenderer.cpp
    Engine/Scene/Components/MeshRenderer.h
    Engine/Scene/Components/ScriptComponent.h
    Engine/Scene/Components/TransformComponent.cpp
    Engine/Scene/Components/TransformComponent.h
    Engine/Scene/EditorCamera.cpp
    Engine/Scene/EditorCamera.h
    Engine/Scene/Entity.cpp
    Engine/Scene/EntityFactory.cpp
    Engine/Scene/EntityFactory.h
    Engine/Scene/Entity.h
    Engine/Scene/Scene.cpp
    Engine/Scene/Scene.h
    Engine/Scene/SceneSerializer.cpp
    Engine/Scene/SceneSerializer.h
)

add_library(Engine STATIC ${ENGINE_SOURCES})
add_library(OpenGLRenderer::Engine ALIAS Engine)

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
)

if(Stb_FOUND)
    target_include_directories(Engine PUBLIC ${Stb_INCLUDE_DIR})
endif()

set(APP_SOURCES
    Application/GameLayer.cpp
    Application/GameLayer.h
    Application/main.cpp
    Application/SandboxLayer.cpp
    Application/SandboxLayer.h
    Application/ShaderTestLayer.cpp
    Application/ShaderTestLayer.h
)

add_executable(OpenGLRenderer ${APP_SOURCES})
target_link_libraries(OpenGLRenderer PRIVATE Engine)

# --- Asset Management ---
add_custom_command(TARGET OpenGLRenderer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/res ${CMAKE_BINARY_DIR}/bin/res
    COMMENT "Copying resources to build directory"
)

# --- Installation ---
install(TARGETS OpenGLRenderer Engine
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
