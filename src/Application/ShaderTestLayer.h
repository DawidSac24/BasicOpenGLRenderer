#pragma once

#include "Engine/Core/Layer.h"
#include "Engine/Events/WindowEvents.h"
#include "Engine/Platform/OpenGL/Application.h"
#include "Engine/Scene/Scene.h"
#include <memory>

class ShaderTestLayer : public Core::Layer
{
public:
    ShaderTestLayer();
    virtual ~ShaderTestLayer() = default;

    virtual void onUpdate() override;
    virtual void onRender() override;

    virtual void onEvent(Core::Event& event) override;
    bool onWindowResize(Core::WindowResizeEvent& e);

    virtual void onDetach() override { }

private:
    std::shared_ptr<Engine::Scene> m_activeScene;
};
