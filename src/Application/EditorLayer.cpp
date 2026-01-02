#include "EditorLayer.h"

#include "Engine/Core/keyCodes.h"
#include "Engine/Events/InputEvents.h"
#include "Engine/ImGui/ImGuiImpl.h"
#include "Engine/ImGui/MenuItems.h"
#include "Engine/Platform/OpenGL/Application.h"
#include "Engine/Scene/Components/CameraComponent.h"
#include "Engine/Scene/Entity.h"
#include "Engine/Scene/Scene.h"

#include "imgui.h"

EditorLayer::EditorLayer()
{
    m_application = &Core::Application::get();

    Gui::Menu viewMenu("View");
    viewMenu.addItem(std::make_shared<Gui::MenuFlagItem>("Scene", &m_hierarchyPanel.isDisplayed));
    viewMenu.addItem(std::make_shared<Gui::MenuFlagItem>("Inspector", &m_inspectorPanel.isDisplayed));

    m_menuBar.addMenu(viewMenu);

    Gui::Menu entityMenu("Entity");

    for (int i = 0; i < (int)Engine::EntityType::Count; i++)
    {
        Engine::EntityType type = (Engine::EntityType)i;

        std::string label = "Add " + EntityTypeToString(type);

        entityMenu.addItem(std::make_shared<Gui::MenuActionItem>(label, [this, type]()
        {
            if (auto scene = Core::Application::get().getActiveScene())
            {
                scene->createEntity("New " + EntityTypeToString(type), type);
            }
        }));
    }

    m_menuBar.addMenu(entityMenu);
}

EditorLayer::~EditorLayer()
{
}

void EditorLayer::onUpdate()
{
    auto scene = Core::Application::get().getActiveScene();
    m_hierarchyPanel.setContext(scene.get());
    m_inspectorPanel.setSelectedEntity(m_hierarchyPanel.getSelectedEntity());
}

void EditorLayer::onRender()
{
    renderUI();
}

void EditorLayer::onEvent(Core::Event& event)
{
    Core::EventDispatcher dispatcher(event);

    dispatcher.dispatch<Core::KeyPressedEvent>([this](Core::KeyPressedEvent& e)
    {
        return onKeyPressed(e);
    });
}

bool EditorLayer::onKeyPressed(Core::KeyPressedEvent& event)
{
    if (event.getKeyCode() == Core::Key::Delete)
    {
        Engine::Entity* selected = m_hierarchyPanel.getSelectedEntity();
        if (selected)
        {
            auto scene = Core::Application::get().getActiveScene();
            scene->destroyEntity(selected);
            m_hierarchyPanel.setSelectedEntity(nullptr);
            return true;
        }
    }
    return false;
}

void EditorLayer::onDetach()
{
}

void EditorLayer::renderUI()
{
    Gui::ImGuiImpl::begin();

    m_menuBar.render();

    m_hierarchyPanel.onImGuiRender();
    m_inspectorPanel.onImGuiRender();

    Gui::ImGuiImpl::end();
}

void EditorLayer::drawEntityNode(Engine::Entity* entity)
{
    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;

    // Highlight if selected
    if (m_selectedEntity == entity)
        flags |= ImGuiTreeNodeFlags_Selected;

    // Mark as leaf if no children
    if (entity->getChildren().empty())
        flags |= ImGuiTreeNodeFlags_Leaf;

    // We cast the ID to void* for ImGui's ID system
    // Assuming entity->name is a std::string
    bool opened = ImGui::TreeNodeEx((void*)(uint64_t)entity->getID(), flags, "%s", entity->name.c_str());

    if (ImGui::IsItemClicked())
    {
        m_selectedEntity = entity;
    }

    if (opened)
    {
        for (auto child : entity->getChildren())
        {
            drawEntityNode(child);
        }
        ImGui::TreePop();
    }
}
