#include "SandboxLayer.h"

#include "Engine/Math/Transform.h"
#include "Engine/Platform/OpenGL/Application.h"
#include "Engine/Renderer/Renderer.h"
#include "Engine/Scene/Components/CameraComponent.h"

SandboxLayer::SandboxLayer()
{
    Core::Application& app = Core::Application::get();
    m_activeScene = app.getActiveScene();

    m_CameraEntity = m_activeScene->getPrimaryCamera();

    m_CameraEntity->getTransform()->setPosition({ 0.0f, 0.0f, 5.0f });
}

void SandboxLayer::onUpdate()
{
    // Spin the cube every frame
    if (m_CubeEntity)
    {
        m_rotation += 0.5f;

        glm::quat rotation = glm::angleAxis(glm::radians(m_rotation), glm::normalize(glm::vec3(1.0f, 1.0f, 0.0f)));

        m_CubeEntity->transform->setRotation(rotation);
    }
}

void SandboxLayer::onRender()
{
}

void SandboxLayer::onEvent(Core::Event& event)
{
}
