#pragma once

#include "Engine/Core/Layer.h"
#include "Engine/Scene/Entity.h"
#include "Engine/Scene/Scene.h"

#include <memory>

class SandboxLayer : public Core::Layer
{
public:
    SandboxLayer();
    virtual ~SandboxLayer() = default;

    virtual void onUpdate() override;
    virtual void onRender() override;

    virtual void onEvent(Core::Event& event) override;

    virtual void onDetach() override { }

private:
    std::shared_ptr<Engine::Scene> m_activeScene = nullptr;

    // Store raw pointers to the entities we want to manipulate
    // (The Scene owns the memory, we just reference them)
    Engine::Entity* m_CameraEntity = nullptr;
    Engine::Entity* m_CubeEntity = nullptr;

    float m_rotation = 0.0f;
};
