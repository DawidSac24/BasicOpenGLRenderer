#include "Scene.h"
#include "GameObject.h"
#include "imgui.h"
#include <memory>

namespace Engine
{

Scene::Scene(const std::string& name)
    : name(name)
{
}

void Scene::onGuiRender()
{
    ImGui::Begin("Scene");
    if (ImGui::TreeNode("Scene Hierarchy"))
    {
        static ImGuiTreeNodeFlags base_flags
            = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;
        static bool align_label_with_current_x_position = false;
        static bool test_drag_and_drop = false;

        // 'selection_mask' is dumb representation of what may be user-side selection state.
        //  You may retain selection state inside or outside your objects in whatever format you see fit.
        // 'node_clicked' is temporary storage of what node we have clicked to process selection at the end
        /// of the loop. May be a pointer to your own node type, etc.
        static int selection_mask = (1 << 2);
        int node_clicked = -1;
        for (int i = 0; i < 6; i++)
        {
            // Disable the default "open on single-click behavior" + set Selected flag according to our selection.
            // To alter selection we use IsItemClicked() && !IsItemToggledOpen(), so clicking on an arrow doesn't alter
            // selection.
            ImGuiTreeNodeFlags node_flags = base_flags;
            const bool is_selected = (selection_mask & (1 << i)) != 0;
            if (is_selected)
                node_flags |= ImGuiTreeNodeFlags_Selected;
            if (i < 3)
            {
                // Items 0..2 are Tree Node
                bool node_open = ImGui::TreeNodeEx((void*)(intptr_t)i, node_flags, "Selectable Node %d", i);
                if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
                    node_clicked = i;
                if (test_drag_and_drop && ImGui::BeginDragDropSource())
                {
                    ImGui::SetDragDropPayload("_TREENODE", NULL, 0);
                    ImGui::Text("This is a drag and drop source");
                    ImGui::EndDragDropSource();
                }
                if (i == 2 && (base_flags & ImGuiTreeNodeFlags_SpanLabelWidth))
                {
                    // Item 2 has an additional inline button to help demonstrate SpanLabelWidth.
                    ImGui::SameLine();
                    if (ImGui::SmallButton("button"))
                    {
                    }
                }
                if (node_open)
                {
                    ImGui::BulletText("Blah blah\nBlah Blah");
                    ImGui::SameLine();
                    ImGui::SmallButton("Button");
                    ImGui::TreePop();
                }
            }
            else
            {
                // Items 3..5 are Tree Leaves
                // The only reason we use TreeNode at all is to allow selection of the leaf. Otherwise we can
                // use BulletText() or advance the cursor by GetTreeNodeToLabelSpacing() and call Text().
                node_flags
                    |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen; // ImGuiTreeNodeFlags_Bullet
                ImGui::TreeNodeEx((void*)(intptr_t)i, node_flags, "Selectable Leaf %d", i);
                if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
                    node_clicked = i;
                if (test_drag_and_drop && ImGui::BeginDragDropSource())
                {
                    ImGui::SetDragDropPayload("_TREENODE", NULL, 0);
                    ImGui::Text("This is a drag and drop source");
                    ImGui::EndDragDropSource();
                }
            }
        }
        if (node_clicked != -1)
        {
            // Update selection state
            // (process outside of tree loop to avoid visual inconsistencies during the clicking frame)
            if (ImGui::GetIO().KeyCtrl)
                selection_mask ^= (1 << node_clicked); // Ctrl+Click to toggle
            else // if (!(selection_mask & (1 << node_clicked))) // Depending on selection behavior you want, may want
                 // to preserve selection when clicking on item that is part of the selection
                selection_mask = (1 << node_clicked); // Click to single-select
        }
        if (align_label_with_current_x_position)
            ImGui::Indent(ImGui::GetTreeNodeToLabelSpacing());
        ImGui::TreePop();
    }
    ImGui::End();
}

GameObject* Scene::getGameObjectByUUID(Core::UUID uuid)
{
    auto it = m_entityMap.find(uuid);
    if (it != m_entityMap.end())
        return it->second.get();

    return nullptr;
}

GameObject* Scene::createGameObject(const std::string& p_name)
{
    std::shared_ptr<GameObject> newObj = std::make_shared<GameObject>(p_name);
    m_entityMap[newObj->getID()] = newObj;

    return newObj.get();
}
GameObject* Scene::createGameObject()
{
    std::shared_ptr<GameObject> newObj = std::make_shared<GameObject>();
    m_entityMap[newObj->getID()] = newObj;

    return newObj.get();
}

void Scene::destroyGameObject(GameObject* obj)
{
    if (!obj)
        return;

    m_entityMap.erase(obj->getID());
}
void Scene::destroyGameObject(Core::UUID id)
{
    m_entityMap.erase(id);
}
}
