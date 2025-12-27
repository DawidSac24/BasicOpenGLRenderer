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
    m_activeScene = application.getActiveScene();
};

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
