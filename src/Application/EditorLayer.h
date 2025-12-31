#pragma once

#include "Engine/Core/Layer.h"
#include "Engine/ImGui/ImGuiImpl.h"
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
    virtual void onDetach() override;

    void renderUI();

private:
    void drawEntityNode(Engine::Entity* entity);
    void drawComponents(Engine::Entity* entity);

    template <typename T, typename UIFunction>
    void drawComponent(const std::string& name, Engine::Entity* entity, UIFunction uiFunction)
    {
        const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen
            | ImGuiTreeNodeFlags_Framed
            | ImGuiTreeNodeFlags_SpanAvailWidth
            | ImGuiTreeNodeFlags_AllowOverlap
            | ImGuiTreeNodeFlags_FramePadding;

        if (entity->hasComponent<T>())
        {
            auto& component = *entity->getComponent<T>();
            ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();

            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2 { 4, 4 });

            // Draw a separator line before the component
            float lineHeight = ImGui::GetFont()->FontSize + ImGui::GetStyle().FramePadding.y * 2.0f;
            ImGui::Separator();

            // Draw Header
            // We use the hash_code of the type as the ID to ensure uniqueness
            bool open = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), treeNodeFlags, "%s", name.c_str());

            // Context Menu (Right Click on Header)
            bool removeComponent = false;
            if (ImGui::BeginPopupContextItem())
            {
                if (ImGui::MenuItem("Remove Component"))
                    removeComponent = true;

                ImGui::EndPopup();
            }

            ImGui::PopStyleVar();

            if (open)
            {
                uiFunction(component);
                ImGui::TreePop();
            }

            // Defer removal until after we are done drawing to avoid crashing the iterator/pointer
            if (removeComponent)
                entity->removeComponent<T>();
        }
    }

private:
    Core::Application* m_application = nullptr;
    Core::ImGuiImpl* m_gui = nullptr;

    // Scene & Selection
    Engine::Scene* m_activeScene = nullptr;
    Engine::Entity* m_selectedEntity = nullptr;

    // Editor Window States (Added these so the MenuBar works)
    bool m_showSceneWindow = true;
    bool m_showInspectorWindow = true;
    bool m_showOptionsWindow = false;
};
