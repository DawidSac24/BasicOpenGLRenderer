#pragma once

#include "Engine/ImGui/ImGuiImpl.h"
#include "Engine/Scene/Components/CameraComponent.h"
#include "Engine/Scene/Components/MeshRenderer.h"
#include "Engine/Scene/Components/TransformComponent.h"
#include "Engine/Scene/Entity.h"
#include "Engine/Scene/Scene.h"

#include <cstring>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>
#include <string>

namespace Gui
{

class SceneHierarchyPanel
{
public:
    bool isDisplayed = false;

public:
    SceneHierarchyPanel() = default;

    void setContext(Engine::Scene* scene) { m_context = scene; }

    Engine::Entity* getSelectedEntity() const { return m_selectedEntity; }
    void setSelectedEntity(Engine::Entity* entity) { m_selectedEntity = entity; }

    void onImGuiRender()
    {
        ImGui::Begin("Scene Hierarchy");

        if (m_context)
        {
            for (auto& entity : *m_context->getEntityList())
            {
                if (entity->getParent() == nullptr)
                    drawEntityNode(entity);
            }

            if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
                m_selectedEntity = nullptr;

            if (ImGui::BeginPopupContextWindow(0, 1))
            {
                if (ImGui::MenuItem("Create Empty Entity"))
                    m_context->createEntity("Empty Entity", Engine::EntityType::Empty);
                ImGui::EndPopup();
            }
        }

        ImGui::End();
    }

private:
    Engine::Scene* m_context = nullptr;
    Engine::Entity* m_selectedEntity = nullptr;

    void drawEntityNode(Engine::Entity* entity)
    {
        ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;

        if (m_selectedEntity == entity)
            flags |= ImGuiTreeNodeFlags_Selected;

        if (entity->getChildren().empty())
            flags |= ImGuiTreeNodeFlags_Leaf;

        // Use generic void* casting for ID
        bool opened = ImGui::TreeNodeEx((void*)(uint64_t)entity->getID(), flags, "%s", entity->name.c_str());

        if (ImGui::IsItemClicked())
            m_selectedEntity = entity;

        if (opened)
        {
            for (auto child : entity->getChildren())
                drawEntityNode(child);
            ImGui::TreePop();
        }
    }
};

class InspectorPanel
{
public:
    bool isDisplayed = false;

public:
    InspectorPanel() = default;

    void setSelectedEntity(Engine::Entity* entity) { m_selectedEntity = entity; }

    void onImGuiRender()
    {
        ImGui::Begin("Inspector");
        if (m_selectedEntity)
        {
            drawNameField();

            drawComponents(m_selectedEntity);

            ImGui::Separator();
            if (ImGui::Button("Add Component"))
                ImGui::OpenPopup("AddComponentPopup");

            if (ImGui::BeginPopup("AddComponentPopup"))
            {
                if (!m_selectedEntity->hasComponent<Engine::CameraComponent>())
                {
                    if (ImGui::MenuItem("Camera"))
                    {
                        m_selectedEntity->addComponent<Engine::CameraComponent>(m_selectedEntity);
                        ImGui::CloseCurrentPopup();
                    }
                }
                if (!m_selectedEntity->hasComponent<Engine::MeshRenderer>())
                {
                    if (ImGui::MenuItem("Mesh Renderer"))
                    {
                        m_selectedEntity->addComponent<Engine::MeshRenderer>(m_selectedEntity);
                        ImGui::CloseCurrentPopup();
                    }
                }
                ImGui::EndPopup();
            }
        }
        ImGui::End();
    }

private:
    Engine::Entity* m_selectedEntity = nullptr;

    void drawNameField()
    {
        char buffer[256];
        memset(buffer, 0, sizeof(buffer));
        strncpy(buffer, m_selectedEntity->name.c_str(), sizeof(buffer) - 1);

        if (ImGui::InputText("##Name", buffer, sizeof(buffer)))
            m_selectedEntity->name = std::string(buffer);
    }

    void drawComponents(Engine::Entity* entity)
    {
        drawComponent<Engine::TransformComponent>("Transform", entity, [](auto& component)
        {
            glm::vec3 pos = component.position;

            // 2. Pass local variable to helper
            if (ImGuiImpl::drawVec3Control("Position", pos))
            {
                // 3. Write back ONLY if changed
                component.position = pos;
            }

            // --- ROTATION ---
            glm::vec3 euler = glm::degrees(glm::eulerAngles(component.rotation));

            if (ImGuiImpl::drawVec3Control("Rotation", euler))
            {
                component.rotation = glm::quat(glm::radians(euler));
            }

            // --- SCALE ---
            glm::vec3 scale = component.scale;

            if (ImGuiImpl::drawVec3Control("Scale", scale))
            {
                component.scale = scale;
            }
        });
        drawComponent<Engine::CameraComponent>("Camera", entity, [entity](auto& component) // <--- CAPTURE entity here
        {
            bool isPrimary = component.isPrimary();

            if (ImGui::Checkbox("Primary", &isPrimary))
            {
                component.setIsPrimary(isPrimary);

                if (isPrimary)
                {
                    if (auto scene = entity->getScene())
                    {
                        scene->setPrimaryCamera(entity);
                    }
                }
            }

            ImGui::DragFloat("FOV", &component.fov);
        });

        drawComponent<Engine::MeshRenderer>("Mesh Renderer", entity, [](auto& component)
        {
            if (component.mesh)
                ImGui::Text("Mesh: Loaded");
        });
    }

    // Generic Helper for UI Node Styling
    template <typename T, typename UIFunction>
    static void drawComponent(const std::string& name, Engine::Entity* entity, UIFunction uiFunction)
    {
        if (!entity->hasComponent<T>())
            return;

        const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowOverlap | ImGuiTreeNodeFlags_FramePadding;

        auto& component = *entity->getComponent<T>();

        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2 { 4, 4 });
        ImGui::Separator();
        bool open = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), treeNodeFlags, "%s", name.c_str());
        ImGui::PopStyleVar();

        if (open)
        {
            uiFunction(component);
            ImGui::TreePop();
        }
    }
};
}
