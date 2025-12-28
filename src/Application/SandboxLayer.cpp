#include "SandboxLayer.h"

#include "Engine/Math/Transform.h"
#include "Engine/Platform/OpenGL/Application.h"
#include "Engine/Renderer/Renderer.h"
#include "Engine/Scene/Components/CameraComponent.h"

SandboxLayer::SandboxLayer()
{
    Core::Application& app = Core::Application::get();
    m_activeScene = app.getActiveScene();

    // 1. Create the Camera
    // Your EntityFactory (inside Scene::createEntity) should attach the CameraComponent
    m_CameraEntity = m_activeScene->createEntity("Main Camera", Engine::EntityType::Camera);

    // IMPORTANT: Move the camera BACK so it can see the object!
    // (Default is 0,0,0, which is inside the cube)
    m_CameraEntity->transform->setPosition({ 0.0f, 0.0f, 5.0f });

    // Set initial aspect ratio
    const auto& camComp = m_CameraEntity->getComponent<Engine::CameraComponent>();
    glm::vec2 windowSize = app.getWindow()->getFrameBufferSize();
    camComp->setViewportSize(windowSize.x, windowSize.y);

    // 2. Create the Cube
    // Your EntityFactory should attach MeshRenderer + Transform
    m_CubeEntity = m_activeScene->createEntity("First Cube", Engine::EntityType::Cube);
}

void SandboxLayer::onUpdate()
{
    // Spin the cube every frame
    if (m_CubeEntity)
    {
        m_rotation += 0.5f;

        // Update the Transform Component directly
        // The Scene::onRender will pick up this new matrix automatically
        glm::quat rotation = glm::quat(glm::vec3(glm::radians(m_rotation * 0.5f), // Pitch (X axis)
            glm::radians(m_rotation), // Yaw   (Y axis)
            0.0f // Roll  (Z axis)
            ));
        m_CubeEntity->transform->setRotation(rotation);
    }
}

void SandboxLayer::onRender()
{
    // 1. Clear Screen
    Renderer::RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1 });
    Renderer::RenderCommand::clear();

    // 2. Let the Scene do the work!
    // This calls Renderer::beginScene(), loops through entities, and calls submit()
    if (m_activeScene)
        m_activeScene->onRender();
}

void SandboxLayer::onEvent(Core::Event& event)
{
    if (event.getEventType() == Core::EventType::WindowResize)
    {
        onWindowResize((Core::WindowResizeEvent&)event);
    }
}

bool SandboxLayer::onWindowResize(Core::WindowResizeEvent& e)
{
    if (e.getWidth() == 0 || e.getHeight() == 0)
        return false;

    Renderer::RenderCommand::setViewport(0, 0, e.getWidth(), e.getHeight());

    // Update the Camera Component
    if (m_CameraEntity)
    {
        const auto& cam = m_CameraEntity->getComponent<Engine::CameraComponent>();
        cam->setViewportSize(e.getWidth(), e.getHeight());
    }

    return false;
}
