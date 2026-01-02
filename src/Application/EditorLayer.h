#pragma once

#include "EditorPanels.h"
#include "Engine/Core/Layer.h"
#include "Engine/Events/InputEvents.h"
#include "Engine/ImGui/ImGuiImpl.h"
#include "Engine/ImGui/MenuItems.h"
#include "Engine/Platform/OpenGL/Application.h"
#include "Engine/Scene/Entity.h"
#include "Engine/Scene/Scene.h"

#include "imgui.h"
#include <string>
#include <typeinfo>

class EditorLayer : public Core::Layer
{
public:
    EditorLayer();
    virtual ~EditorLayer();

    virtual void onUpdate() override;
    virtual void onRender() override;
    virtual void onEvent(Core::Event& event) override;
    bool onKeyPressed(Core::KeyPressedEvent& event);
    virtual void onDetach() override;

    void renderUI();

private:
    Core::Application* m_application = nullptr;

    Engine::Scene* m_activeScene = nullptr;
    Engine::Entity* m_selectedEntity = nullptr;

    Gui::MenuBar m_menuBar;

    Gui::SceneHierarchyPanel m_hierarchyPanel;
    Gui::InspectorPanel m_inspectorPanel;

private:
    void drawEntityNode(Engine::Entity* entity);
};
