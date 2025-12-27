#include "EditorLayer.h"

#include "Engine/Platform/OpenGL/Application.h"
#include "Engine/Scene/Entity.h"
#include "Engine/Scene/Scene.h"

#include "imgui.h"
#include <memory>

EditorLayer::EditorLayer()
{
    m_application = &Core::Application::get();
    m_gui = m_application->getGui().get();
}

EditorLayer::~EditorLayer() { }

void EditorLayer::onUpdate() { }

void EditorLayer::onRender()
{
    onGuiRender();
}

void EditorLayer::onGuiRender()
{
    m_gui->begin();
    ImGui::Begin("Scene Hierarchy");

    auto scene = Core::Application::get().getActiveScene();
    if (scene)
    {

        for (auto& [uuid, entity] : *scene->getEntityMap())
        {
            // If it has a parent, it will be drawn by the recursion in DrawEntityNode.
            if (entity.get()->getParent() == nullptr)
            {
                drawEntityNode(entity.get());
            }
        }

        // Deselect if clicking in empty space
        if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
            m_selectedEntity = nullptr;
    }
    ImGui::End();

    // --- Inspector Panel ---
    ImGui::Begin("Inspector");
    if (m_selectedEntity)
    {
        drawComponents(m_selectedEntity);
    }

    ImGui::End();
    m_gui->end();
}

void EditorLayer::onEvent(Core::Event& event) { }

void EditorLayer::onDetach() { }

void EditorLayer::drawEntityNode(Engine::Entity* entity)
{
    // 1. Setup Flags
    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;

    // Highlight if selected
    if (m_selectedEntity == entity)
        flags |= ImGuiTreeNodeFlags_Selected;

    // Remove the "arrow" if it has no children (makes it look like a leaf)
    if (entity->getChildren().empty())
        flags |= ImGuiTreeNodeFlags_Leaf;

    bool opened = ImGui::TreeNodeEx((void*)(uint64_t)entity->getID(), flags, "%s", entity->name.c_str());

    // Handle Selection
    if (ImGui::IsItemClicked())
    {
        m_selectedEntity = entity;
    }

    // Draw Children
    if (opened)
    {
        for (auto child : entity->getChildren())
        {
            drawEntityNode(child);
        }
        ImGui::TreePop(); // Close the folder
    }
}

void EditorLayer::drawComponents(Engine::Entity* entity)
{
    auto& components = *entity->getComponents();

    for (auto& component : components)
    {
        component->onGuiRender();
    }
}
