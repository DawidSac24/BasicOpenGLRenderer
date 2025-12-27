#pragma once

#include "Engine/Renderer/Material.h"
#include "Engine/Renderer/Mesh.h"
#include "Engine/Renderer/Renderer.h"
#include "Engine/Scene/Components/Component.h"
#include "glm/gtc/type_ptr.hpp"
#include "imgui.h"

#include <memory>

namespace Engine
{
class MeshRenderer : public Component
{
public:
    std::shared_ptr<Renderer::Mesh> mesh = nullptr;
    std::shared_ptr<Renderer::Material> material;

public:
    MeshRenderer() = default;

    MeshRenderer(std::shared_ptr<Renderer::Mesh> m, std::shared_ptr<Renderer::Material> mat)
        : mesh(m)
        , material(mat)
    {
    }

    virtual void onRender() override
    {
        if (!mesh || !material)
            return;

        auto& transformComponent = owner->transform;
        glm::mat4 transformMatrix = transformComponent->getWorldMatrix();

        Renderer::Renderer::submit(mesh, material, transformMatrix);
    }

    virtual void onGuiRender() override
    {
        // Use a collapsing header so we can hide/show the component
        if (ImGui::CollapsingHeader("Mesh Renderer", ImGuiTreeNodeFlags_DefaultOpen))
        {
            // --- 1. MESH SECTION ---
            ImGui::Text("Mesh Asset");
            if (mesh)
            {
                // Display basic stats
                ImGui::BulletText("Vertices: %d", mesh->getIndexCount()); // Assuming index count roughly correlates

                // In a real engine, you would have a button here to swap the mesh
                if (ImGui::Button("Swap Mesh"))
                {
                    // Open Asset Popup logic...
                }
            }
            else
            {
                ImGui::TextColored(ImVec4(1, 0, 0, 1), "No Mesh Loaded!");
            }

            ImGui::Separator();

            // --- 2. MATERIAL SECTION ---
            ImGui::Text("Material");

            if (material)
            {
                // A. Edit Uniforms (Colors/Vectors)
                // We reference the map directly so changes update the material instantly
                auto& uniforms = material->getUniforms();

                for (auto& [name, value] : uniforms)
                {
                    ImGui::PushID(name.c_str()); // Ensure ImGui IDs are unique per uniform

                    // Heuristic: If the name contains "Color", show a Color Picker. Otherwise show sliders.
                    if (name.find("Color") != std::string::npos || name.find("color") != std::string::npos)
                    {
                        ImGui::ColorEdit4(name.c_str(), glm::value_ptr(value));
                    }
                    else
                    {
                        ImGui::DragFloat4(name.c_str(), glm::value_ptr(value), 0.1f);
                    }

                    ImGui::PopID();
                }

                ImGui::Spacing();

                // B. Edit Textures
                auto& textures = material->getTextures();
                for (auto& [name, texture] : textures)
                {
                    ImGui::Text("%s:", name.c_str());

                    if (texture)
                    {
                        // Show a small thumbnail preview of the texture
                        // (void*)(intptr_t) casts the GL ID to an ImGui Texture ID
                        ImGui::Image(
                            (void*)(intptr_t)texture->getRendererID(), ImVec2(64, 64), ImVec2(0, 1), ImVec2(1, 0));

                        if (ImGui::IsItemHovered())
                        {
                            ImGui::BeginTooltip();
                            ImGui::Text("Texture ID: %d", texture->getRendererID());
                            ImGui::EndTooltip();
                        }
                    }
                    else
                    {
                        ImGui::Button("Empty (Drag Texture Here)");
                    }
                }
            }
            else
            {
                ImGui::TextColored(ImVec4(1, 0, 0, 1), "No Material Assigned!");
                if (ImGui::Button("Create Default Material"))
                {
                    // Assign a default material logic here
                }
            }
        }
    }
};
}
