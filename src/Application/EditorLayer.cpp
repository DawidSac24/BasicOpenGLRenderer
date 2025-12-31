#include "EditorLayer.h"

// Engine Includes
#include "Engine/Core/keyCodes.h"
#include "Engine/Events/InputEvents.h"
#include "Engine/Platform/OpenGL/Application.h"
#include "Engine/Scene/Components/CameraComponent.h"
#include "Engine/Scene/Components/MeshRenderer.h"
#include "Engine/Scene/Components/TransformComponent.h" // Ensure this is included
#include "Engine/Scene/Entity.h"
#include "Engine/Scene/Scene.h"

// Third Party
#include "glm/gtc/type_ptr.hpp"
#include "imgui.h"
#include <cstring>

EditorLayer::EditorLayer()
{
    m_application = &Core::Application::get();
    // Assuming m_gui is a shared_ptr or unique_ptr in Application
    m_gui = m_application->getGui().get();
}

EditorLayer::~EditorLayer()
{
}

void EditorLayer::onUpdate()
{
    // Update logic (e.g., camera movement, shortcuts) goes here
}

void EditorLayer::onRender()
{
    renderUI();
}

void EditorLayer::onEvent(Core::Event& event)
{
    // Create a dispatcher
    Core::EventDispatcher dispatcher(event);

    // Dispatch KeyPressedEvent to our handler
    dispatcher.dispatch<Core::KeyPressedEvent>([this](Core::KeyPressedEvent& e)
        { return onKeyPressed(e); });
}

bool EditorLayer::onKeyPressed(Core::KeyPressedEvent& event)
{
    // 1. Check if the pressed key is "Delete"
    if (event.getKeyCode() == Core::Key::Delete)
    {
        // 2. Ensure we have a valid selection
        if (m_selectedEntity)
        {
            // 3. Get Scene
            auto scene = Core::Application::get().getActiveScene();
            if (scene)
            {
                // 4. Remove the entity
                scene->destroyEntity(m_selectedEntity);

                // 5. Clear selection so we don't crash accessing a dead pointer later
                m_selectedEntity = nullptr;

                return true; // Consume the event
            }
        }
    }
    return false;
}

void EditorLayer::onDetach()
{
}

// --- Main UI Rendering ---
void EditorLayer::renderUI()
{
    // Start the ImGui Frame
    m_gui->begin();

    // 1. Menu Bar
    if (ImGui::BeginMainMenuBar())
    {
        // --- A. File / View Menus ---
        if (ImGui::BeginMenu("View"))
        {
            ImGui::MenuItem("Scene", nullptr, &m_showSceneWindow);
            ImGui::MenuItem("Inspector", nullptr, &m_showInspectorWindow);
            ImGui::MenuItem("Engine Options", nullptr, &m_showOptionsWindow);
            ImGui::EndMenu();
        }

        // --- B. Entity Creation Menu (NEW) ---
        if (ImGui::BeginMenu("Entity"))
        {
            auto scene = Core::Application::get().getActiveScene();

            if (scene)
            {
                if (ImGui::MenuItem("Add Empty"))
                {
                    scene->createEntity("Empty Entity", Engine::EntityType::Empty);
                }

                if (ImGui::MenuItem("Add Square"))
                {
                    scene->createEntity("Square", Engine::EntityType::Cube);
                }

                if (ImGui::MenuItem("Add Cube"))
                {
                    scene->createEntity("Cube", Engine::EntityType::Cube);
                }
            }
            else
            {
                ImGui::TextDisabled("No Active Scene");
            }

            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }

    // 2. Scene Hierarchy Panel
    if (m_showSceneWindow)
    {
        ImGui::Begin("Scene Hierarchy", &m_showSceneWindow);

        auto scene = Core::Application::get().getActiveScene();
        if (scene)
        {
            // Iterate through all entities in the list
            // Note: Ensure getEntityList() returns a container that preserves order (std::list)
            for (auto& entity : *scene->getEntityList())
            {
                // Only draw root nodes (parents)
                // If your entity system doesn't have parenting yet, just draw all of them.
                if (entity->getParent() == nullptr)
                {
                    drawEntityNode(entity);
                }
            }

            // Deselect if clicking in empty space
            if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
                m_selectedEntity = nullptr;

            // Context Menu for Scene Panel (Right-click blank space to create)
            if (ImGui::BeginPopupContextWindow(0, 1))
            {
                if (ImGui::MenuItem("Create Empty Entity"))
                    scene->createEntity("Empty Entity", Engine::EntityType::Empty);

                ImGui::EndPopup();
            }
        }
        ImGui::End();
    }

    // 3. Inspector Panel
    if (m_showInspectorWindow)
    {
        ImGui::Begin("Inspector", &m_showInspectorWindow);
        if (m_selectedEntity)
        {
            // Display Name field at the top
            char buffer[256];
            memset(buffer, 0, sizeof(buffer));

            // NEW (Cross-platform)
            // Copy the string, leaving room for the null terminator
            strncpy(buffer, m_selectedEntity->name.c_str(), sizeof(buffer) - 1);

            // Manually ensure the last character is null, just in case the name is too long
            buffer[sizeof(buffer) - 1] = '\0';

            // Allow renaming the entity
            if (ImGui::InputText("##Name", buffer, sizeof(buffer)))
            {
                m_selectedEntity->name = std::string(buffer);
            }

            ImGui::SameLine();
            ImGui::TextDisabled("(ID: %llu)", (uint64_t)m_selectedEntity->getID()); // Debug ID

            ImGui::Separator();

            drawComponents(m_selectedEntity);

            // button to add new components
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

                // Add other components here...

                ImGui::EndPopup();
            }
        }
        ImGui::End();
    }

    m_gui->end();
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

// --- Helper: Draw Components ---
void EditorLayer::drawComponents(Engine::Entity* entity)
{
    // --- 1. Transform Component ---
    drawComponent<Engine::TransformComponent>("Transform", entity, [](auto& component)
        {
        // Position
        float pos[3] = { component.getPosition().x, component.getPosition().y, component.getPosition().z };
        if (ImGui::DragFloat3("Position", pos, 0.1f))
            component.setPosition({ pos[0], pos[1], pos[2] });

        // Rotation (Converting Quaternion to Euler for display)
        glm::vec3 euler = glm::degrees(glm::eulerAngles(component.getRotation()));
        if (ImGui::DragFloat3("Rotation", glm::value_ptr(euler), 0.1f))
        {
            component.setRotation(glm::quat(glm::radians(euler)));
        }

        // Scale
        glm::vec3 scale = component.getScale();
        if (ImGui::DragFloat3("Scale", glm::value_ptr(scale), 0.1f))
            component.setScale(scale); });

    // --- 2. Camera Component ---
    drawComponent<Engine::CameraComponent>("Camera", entity, [](auto& component)
        {
        ImGui::Checkbox("Primary", &component.primary);

        float fov = component.fov;
        if (ImGui::DragFloat("FOV", &fov, 0.1f, 1.0f, 180.0f))
            component.fov = fov;

        ImGui::DragFloat("Near Clip", &component.nearClip, 0.1f);
        ImGui::DragFloat("Far Clip", &component.farClip, 10.0f); });

    // --- 3. Mesh Renderer (With Material Logic) ---
    drawComponent<Engine::MeshRenderer>("Mesh Renderer", entity, [](auto& component)
        {
        // Mesh Info
        if (component.mesh)
            ImGui::Text("Mesh: Loaded (%d indices)", component.mesh->getIndexCount());
        else
            ImGui::TextColored({ 1.0f, 0.0f, 0.0f, 1.0f }, "Mesh: Missing");

        ImGui::Separator();

        // Material Logic
        if (component.material)
        {
            ImGui::Text("Material Properties");

            // A. Uniforms
            auto& uniforms = component.material->getUniforms();
            for (auto& [name, value] : uniforms)
            {
                ImGui::PushID(name.c_str());
                
                // Heuristic: if the name contains "Color", use a color picker
                if (name.find("Color") != std::string::npos)
                    ImGui::ColorEdit4(name.c_str(), glm::value_ptr(value));
                else
                    ImGui::DragFloat4(name.c_str(), glm::value_ptr(value), 0.05f);
                
                ImGui::PopID();
            }

            // B. Textures
            auto& textures = component.material->getTextures();
            for (auto& [name, texture] : textures)
            {
                ImGui::Text("%s:", name.c_str());
                if (texture)
                {
                    // Render Image Preview
                    ImGui::Image((ImTextureID)(intptr_t)texture->getRendererID(), 
                        ImVec2(64, 64), 
                        ImVec2(0, 1), 
                        ImVec2(1, 0));
                }
                else 
                {
                    ImGui::TextDisabled("Empty Slot");
                }
            }
        } });
}
