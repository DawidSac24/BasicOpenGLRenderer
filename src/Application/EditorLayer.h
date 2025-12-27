#pragma once

#include "Engine/Core/Layer.h"
#include "Engine/ImGui/ImGuiImpl.h"
#include "Engine/Platform/OpenGL/Application.h"
#include "Engine/Scene/Entity.h"
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

    virtual void onGuiRender();

private:
    Core::Application* m_application = nullptr;
    Core::ImGuiImpl* m_gui = nullptr;

    Engine::Scene* m_activeScene = nullptr;
    Engine::Entity* m_selectedEntity = nullptr;

private:
    void drawEntityNode(Engine::Entity* entinty);
    void drawComponents(Engine::Entity* entity);
};
