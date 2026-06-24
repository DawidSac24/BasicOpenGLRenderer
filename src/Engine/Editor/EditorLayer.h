#pragma once

#include "EditorPanels.h"
#include "Engine/Core/Events/InputEvents.h"
#include "Engine/Core/Layer.h"
#include "Engine/ImGui/MenuItems.h"
#include "Engine/Platform/OpenGL/Application.h"
#include "Engine/Scene/Entity.h"
#include "Engine/Scene/Scene.h"

#include <memory>

namespace Engine
{
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

    std::shared_ptr<Engine::Scene> m_activeScene = nullptr;
    Engine::Entity* m_selectedEntity = nullptr;

    Gui::MenuBar m_menuBar;

    Gui::SceneHierarchyPanel m_hierarchyPanel;
    Gui::InspectorPanel m_inspectorPanel;

private:
    void drawEntityNode(Engine::Entity* entity);
};
}
