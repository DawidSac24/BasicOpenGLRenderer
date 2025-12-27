#include "SandboxLayer.h"

#include "Engine/Events/WindowEvents.h"
#include "Engine/Platform/OpenGL/Application.h"
#include "Engine/Renderer/Camera.h"

#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include <memory>

SandboxLayer::SandboxLayer()
{
    Core::Application& application = Core::Application::get();
    glm::vec2 frameBufferSize = application.getWindow()->getFrameBufferSize();

    std::vector<Renderer::Vertex> vertices = {
        // Front Face (Normal 0, 0, 1)
        { { -0.5f, -0.5f, 0.5f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } }, // Bottom-Left
        { { 0.5f, -0.5f, 0.5f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f } }, // Bottom-Right
        { { 0.5f, 0.5f, 0.5f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f } }, // Top-Right
        { { -0.5f, 0.5f, 0.5f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f, 0.0f }, { 0.0f, 1.0f } }, // Top-Left

        // Back Face (Normal 0, 0, -1)
        { { 0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 0.0f, 0.0f },
            { 0.0f, 0.0f } }, // Bottom-Left (from back)
        { { -0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f } }, // Bottom-Right
        { { -0.5f, 0.5f, -0.5f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f } }, // Top-Right
        { { 0.5f, 0.5f, -0.5f }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 1.0f, 0.0f }, { 0.0f, 1.0f } }, // Top-Left

        // Left Face (Normal -1, 0, 0)
        { { -0.5f, -0.5f, -0.5f }, { -1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } },
        { { -0.5f, -0.5f, 0.5f }, { -1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f } },
        { { -0.5f, 0.5f, 0.5f }, { -1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f } },
        { { -0.5f, 0.5f, -0.5f }, { -1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 0.0f }, { 0.0f, 1.0f } },

        // Right Face (Normal 1, 0, 0)
        { { 0.5f, -0.5f, 0.5f }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } },
        { { 0.5f, -0.5f, -0.5f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f } },
        { { 0.5f, 0.5f, -0.5f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f } },
        { { 0.5f, 0.5f, 0.5f }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 0.0f }, { 0.0f, 1.0f } },

        // Top Face (Normal 0, 1, 0)
        { { -0.5f, 0.5f, 0.5f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } },
        { { 0.5f, 0.5f, 0.5f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f } },
        { { 0.5f, 0.5f, -0.5f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f } },
        { { -0.5f, 0.5f, -0.5f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 1.0f, 0.0f }, { 0.0f, 1.0f } },

        // Bottom Face (Normal 0, -1, 0)
        { { -0.5f, -0.5f, -0.5f }, { 0.0f, -1.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } },
        { { 0.5f, -0.5f, -0.5f }, { 0.0f, -1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f } },
        { { 0.5f, -0.5f, 0.5f }, { 0.0f, -1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f } },
        { { -0.5f, -0.5f, 0.5f }, { 0.0f, -1.0f, 0.0f }, { 1.0f, 1.0f, 0.0f }, { 0.0f, 1.0f } },
    };
    // 36 Indices (6 faces * 2 triangles * 3 indices)
    std::vector<GLuint> indices = {
        0, 1, 2, 2, 3, 0, // Front
        4, 5, 6, 6, 7, 4, // Back
        8, 9, 10, 10, 11, 8, // Left
        12, 13, 14, 14, 15, 12, // Right
        16, 17, 18, 18, 19, 16, // Top
        20, 21, 22, 22, 23, 20 // Bottom
    };
    std::vector<GLuint> lineIndices = { // Front Face
        0, 1, 1, 2, 2, 3, 3, 0,
        // Back Face
        4, 5, 5, 6, 6, 7, 7, 4,
        // Left Face
        8, 9, 9, 10, 10, 11, 11, 8,
        // Right Face
        12, 13, 13, 14, 14, 15, 15, 12,
        // Top Face
        16, 17, 17, 18, 18, 19, 19, 16,
        // Bottom Face
        20, 21, 21, 22, 22, 23, 23, 20
    };

    // EMPTY Texture List
    std::vector<Renderer::Texture> noTextures;

    whiteShader
        = std::make_unique<Renderer::Shader>("../res/shaders/whiteShader.vert", "../res/shaders/whiteShader.frag");
    basicShader = std::make_unique<Renderer::Shader>("../res/shaders/basic.vert", "../res/shaders/basic.frag");
    camera = std::make_unique<Renderer::Camera>(frameBufferSize.x, frameBufferSize.y, glm::vec3(0.0f, 0.0f, 2.0f));
    cubeMesh = std::make_unique<Renderer::Mesh>(vertices, indices, noTextures);
    cubeLineMesh = std::make_unique<Renderer::Mesh>(vertices, lineIndices, noTextures);
}
SandboxLayer::~SandboxLayer() { }

void SandboxLayer::onUpdate()
{
    m_rotation += 0.5f;
}

void SandboxLayer::onRender()
{
    // 1. Clear and Prepare
    Renderer::RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1 });
    Renderer::RenderCommand::clear();

    // IMPORTANT: Enable Blending globally for transparency to work
    Renderer::RenderCommand::enableBlending();

    // 2. Begin Scene
    Renderer::Renderer::beginScene(*camera);

    // Calculate generic model matrix
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(m_rotation), glm::vec3(0.0f, 1.0f, 0.0f));

    // --- PASS 1: DRAW TRANSPARENT CUBE ---
    {
        // Disable Depth Mask for transparent objects
        // (So the cube looks "ghostly" and doesn't hide the lines behind it)
        Renderer::RenderCommand::disableDepthMask();

        Renderer::Renderer::submit(cubeMesh, basicShader, model);
    }

    // --- PASS 2: DRAW SOLID LINES ---
    {
        // Re-enable Depth Mask for solid objects (The lines)
        Renderer::RenderCommand::enableDepthMask();

        // Scale slightly bigger so lines sit on top
        glm::mat4 outlineModel = glm::scale(model, glm::vec3(1.01f));

        Renderer::Renderer::submit(cubeLineMesh, whiteShader, outlineModel, GL_LINES);
    }

    Renderer::Renderer::endScene();
}

void SandboxLayer::onEvent(Core::Event& event)
{
    // Check type manually (or use a Dispatcher if you have one)
    if (event.getEventType() == Core::EventType::WindowResize)
    {
        // Cast and call helper
        onWindowResize((Core::WindowResizeEvent&)event);
    }
}

bool SandboxLayer::onWindowResize(Core::WindowResizeEvent& e)
{
    // HYPRLAND FIX: Handle minimization (Size 0,0)
    // If we don't check this, projection matrix calculation divides by zero -> Crash/NaN
    if (e.getWidth() == 0 || e.getHeight() == 0)
        return false;

    // 1. Update Camera Projection (Aspect Ratio)
    // Note: Use 'float' cast to ensure floating point division
    camera->setViewportSize((float)e.getWidth(), (float)e.getHeight());

    // 2. Update OpenGL Viewport
    Renderer::RenderCommand::setViewport(0, 0, e.getWidth(), e.getHeight());

    return false; // Return false so other layers can also see this event (e.g., UI Layer)
}

void SandboxLayer::onDetach() { }
