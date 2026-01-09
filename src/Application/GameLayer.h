#pragma once

#include "Engine/Core/Layer.h"
#include "Engine/Platform/OpenGL/Application.h"
#include <memory>

class GameLayer : public Core::Layer
{
public:
    GameLayer();
    virtual ~GameLayer();

    virtual void onUpdate() override;
    virtual void onRender() override;
    virtual void onEvent(Core::Event& event) override;
    virtual void onDetach() override;

private:
    Core::Application* m_application = nullptr;
    std::shared_ptr<Engine::Scene> m_scene = nullptr;
};
