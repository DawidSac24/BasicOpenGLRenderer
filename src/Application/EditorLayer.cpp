#include "EditorLayer.h"
// Engine Includes
#include "Engine/Core/keyCodes.h"
#include "Engine/Events/InputEvents.h"
#include "Engine/ImGui/MenuItems.h"
#include "Engine/Platform/OpenGL/Application.h"
#include "Engine/Scene/Components/CameraComponent.h"
#include "Engine/Scene/Components/MeshRenderer.h"
#include "Engine/Scene/Components/TransformComponent.h"
#include "Engine/Scene/Entity.h"
#include "Engine/Scene/Scene.h"

#include "glm/gtc/type_ptr.hpp"
#include "imgui.h"

EditorLayer::EditorLayer()
{
    m_application = &Core::Application::get();
    m_gui = m_application->getGui().get();

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
        } }));
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
        { return onKeyPressed(e); });
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
    m_gui->begin();

    m_menuBar.render();

    m_hierarchyPanel.onImGuiRender();
    m_inspectorPanel.onImGuiRender();

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
