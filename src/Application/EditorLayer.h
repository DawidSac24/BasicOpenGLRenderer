#pragma once

#include "Engine/Core/Layer.h"
#include "Engine/ImGui/ImGuiImpl.h"
#include "Engine/Platform/OpenGL/Application.h"
#include "Engine/Scene/Entity.h"
#include "Engine/Scene/Scene.h"
#include "imgui.h"

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

    template <typename T, typename UIFunction>
    void drawComponent(const std::string& name, Engine::Entity* entity, UIFunction uiFunction)
    {
        const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed
            | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowOverlap | ImGuiTreeNodeFlags_FramePadding;

        if (entity->hasComponent<T>())
        {
            auto& component = *entity->getComponent<T>();
            ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();

            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2 { 4, 4 });

            ImGui::Separator();

            // Draw Header
            bool open = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), treeNodeFlags, "%s", name.c_str());
            ImGui::PopStyleVar();

            // Calculate context menu options (Right Click)
            // ... (We can add a "Remove Component" button logic here later)

            if (open)
            {
                uiFunction(component);
                ImGui::TreePop();
            }
        }
    }
};
