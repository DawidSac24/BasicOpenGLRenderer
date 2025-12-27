#pragma once

#include "Components/Component.h"
#include "Scene.h"

#include <algorithm>
#include <memory>
#include <type_traits>
#include <vector>

namespace Math
{
class Transform;
}

namespace Engine
{

enum class EntityType
{
    Empty,
    Square,
    Sphere,
};

class Entity
{
public:
    std::string name = "newEntity";
    std::unique_ptr<Math::Transform> transform;

public:
    Entity(const std::string* name, Entity* parent = nullptr);
    Entity(Core::UUID id, const std::string* name, Entity* parent = nullptr);

    ~Entity() = default;

    // disable copying
    Entity(const Entity&) = delete;
    Entity& operator=(const Entity&) = delete;

    Core::UUID getID() const { return id; }

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

    std::vector<std::unique_ptr<Component>>* getComponents() { return &m_components; }

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

    Entity* getParent() const { return m_parent; }
    const std::vector<Entity*>& getChildren() const { return m_children; }

    void setParent(Entity* parent);

    void markChildrenDirty();

private:
    Core::UUID id;

    std::vector<std::unique_ptr<Component>> m_components;

    Entity* m_parent;
    std::vector<Entity*> m_children;

private:
    void addChild(Entity* child);
    void removeChild(Entity* child);
};
}
