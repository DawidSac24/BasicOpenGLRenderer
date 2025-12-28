#include "EditorLayer.h"

#include "Engine/Platform/OpenGL/Application.h"
#include "Engine/Scene/Components/CameraComponent.h"
#include "Engine/Scene/Components/MeshRenderer.h"
#include "Engine/Scene/Entity.h"
#include "Engine/Scene/Scene.h"

#include "glm/gtc/type_ptr.hpp"
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
    // --- 1. Transform Component ---
    drawComponent<Engine::TransformComponent>("Transform", entity,
        [](auto& component)
        {
            // Position
            float pos[3] = { component.getPosition().x, component.getPosition().y, component.getPosition().z };
            if (ImGui::DragFloat3("Position", pos, 0.1f))
                component.setPosition({ pos[0], pos[1], pos[2] });

            // Rotation (Euler conversion)
            glm::vec3 euler = glm::degrees(glm::eulerAngles(component.getRotation()));
            if (ImGui::DragFloat3("Rotation", glm::value_ptr(euler), 0.1f))
                component.setRotation(glm::quat(glm::radians(euler)));

            // Scale
            glm::vec3 scale = component.getScale();
            if (ImGui::DragFloat3("Scale", glm::value_ptr(scale), 0.1f))
                component.setScale(scale);
        });

    // --- 2. Camera Component ---
    drawComponent<Engine::CameraComponent>("Camera", entity,
        [](auto& component)
        {
            ImGui::Checkbox("Primary", &component.primary);

            float fov = component.fov;
            if (ImGui::DragFloat("FOV", &fov, 0.1f, 1.0f, 180.0f))
                component.fov = fov;

            ImGui::DragFloat("Near Clip", &component.nearClip, 0.1f);
            ImGui::DragFloat("Far Clip", &component.farClip, 10.0f);
        });

    // --- 3. Mesh Renderer (With Material Logic) ---
    drawComponent<Engine::MeshRenderer>("Mesh Renderer", entity,
        [](auto& component)
        {
            // Mesh Info
            if (component.mesh)
                ImGui::Text("Mesh: Loaded (%d indices)", component.mesh->getIndexCount());
            else
                ImGui::TextColored({ 1, 0, 0, 1 }, "Mesh: Missing");

            ImGui::Separator();

            // Material Logic
            if (component.material)
            {
                ImGui::Text("Material Properties");

                // A. Uniforms (Colors)
                auto& uniforms = component.material->getUniforms();
                for (auto& [name, value] : uniforms)
                {
                    ImGui::PushID(name.c_str());
                    if (name.find("Color") != std::string::npos)
                        ImGui::ColorEdit4(name.c_str(), glm::value_ptr(value));
                    else
                        ImGui::DragFloat4(name.c_str(), glm::value_ptr(value), 0.1f);
                    ImGui::PopID();
                }

                // B. Textures
                auto& textures = component.material->getTextures();
                for (auto& [name, texture] : textures)
                {
                    ImGui::Text("%s:", name.c_str());
                    if (texture)
                    {
                        ImGui::Image((ImTextureID)(intptr_t)texture->getRendererID(), ImVec2(64, 64), ImVec2(0, 1),
                            ImVec2(1, 0));
                    }
                }
            }
        });
}
