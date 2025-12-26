// GameObject.h
#pragma once
#include "Component.h"
#include "Maths/Transform.h"
#include "glm/fwd.hpp"
#include <algorithm>
#include <memory>
#include <type_traits>
#include <vector>

namespace Engine
{
class GameObject
{
public:
    std::string name;
    std::unique_ptr<Math::Transform> transform;

public:
    GameObject(const std::string& name, GameObject* parent = nullptr);

    template <typename TComponent>
        requires(std::is_base_of_v<Component, TComponent>)
    TComponent* getComponent()
    {
        for (auto& component : m_components)
        {
            if (TComponent* ptr = dynamic_cast<TComponent*>(component.get()))
            {
                return ptr;
            }
        }
        return nullptr;
    }

    template <typename TComponent, typename... Args>
        requires(std::is_base_of_v<Component, TComponent>)
    TComponent* addComponent(Args&&... args)
    {
        auto newComponent = std::make_unique<TComponent>(std::forward<Args>(args)...);
        newComponent->owner = this;
        TComponent* ptr = newComponent.get();
        m_components.push_back(std::move(newComponent));
        return ptr;
    }

    GameObject* getParent() const { return m_parent; }
    const std::vector<GameObject*>& getChildren() const { return m_children; }

    void setParent(GameObject* parent);

    void markChildrenDirty();

private:
    std::vector<std::unique_ptr<Component>> m_components;

    GameObject* m_parent;
    std::vector<GameObject*> m_children;

private:
    void addChild(GameObject* child);
    void removeChild(GameObject* child);
};
}
