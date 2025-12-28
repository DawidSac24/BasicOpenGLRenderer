#pragma once

#include "Engine/Core/Layer.h"
#include "Engine/Events/WindowEvents.h"
#include "Engine/Scene/Entity.h"
#include "Engine/Scene/Scene.h"

#include <memory>

class SandboxLayer : public Core::Layer
{
private:
    std::shared_ptr<Engine::Scene> m_activeScene = nullptr;

    // Store raw pointers to the entities we want to manipulate
    // (The Scene owns the memory, we just reference them)
    Engine::Entity* m_CameraEntity = nullptr;
    Engine::Entity* m_CubeEntity = nullptr;

    float m_rotation = 0.0f;

public:
    SandboxLayer();
    virtual ~SandboxLayer() = default;

    virtual void onUpdate() override;
    virtual void onRender() override;

    virtual void onEvent(Core::Event& event) override;
    bool onWindowResize(Core::WindowResizeEvent& e);

    virtual void onDetach() override { }
};
