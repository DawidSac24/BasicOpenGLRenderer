#pragma once

#include "Engine/Core/Layer.h"
#include "Engine/Scene/GameObject.h"
#include "Engine/Scene/Scene.h"

class EditorLayer : public Core::Layer
{
public:
    EditorLayer();
    virtual ~EditorLayer();

    virtual void onUpdate() override;
    virtual void onRender() override;

    virtual void onEvent(Core::Event& event) override;

    virtual void onDetach() override;

    virtual void onGuiRender() override;

private:
    Engine::Scene* m_scene = nullptr;
    Engine::GameObject* m_selectedContext = nullptr;
};
