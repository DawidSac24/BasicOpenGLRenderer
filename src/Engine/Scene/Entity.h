#pragma once

#include "Components/Component.h"
#include "Engine/Core/UUID.h"
#include "Engine/Scene/Components/TransformComponent.h"

#include <algorithm>
#include <bits/types/cookie_io_functions_t.h>
#include <list>
#include <memory>
#include <type_traits>
#include <vector>

namespace Math
{
class Transform;
}

namespace Engine
{

class Scene;

enum class EntityType
{
    Unknown,
    Empty,
    Cube,
    Sphere,
    Plane,
    Camera,
    Count,
};

std::string EntityTypeToString(Engine::EntityType type);

class Entity
{
public:
    std::string name = "newEntity";

    TransformComponent* transform;
    std::list<Entity*>::iterator orderIterator;

public:
    Entity(const std::string& name, Scene* scene, Entity* parent = nullptr);
    Entity(Core::UUID id, const std::string& name, Scene* scene, Entity* parent = nullptr);

    ~Entity() = default;

    // disable copying
    Entity(const Entity&) = delete;
    Entity& operator=(const Entity&) = delete;

    Core::UUID getID() const { return id; }

    template <typename TComponent>
        requires(std::is_base_of_v<Component, TComponent>)
    bool hasComponent()
    {
        return getComponent<TComponent>() != nullptr;
    }
    bool hasComponents()
    {
        return !m_components.empty();
    }

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

    TransformComponent* getTransform() { return getComponent<TransformComponent>(); }

    std::vector<std::unique_ptr<Component>>* getComponents() { return &m_components; }

    template <typename TComponent, typename... Args>
        requires(std::is_base_of_v<Component, TComponent>)
    TComponent* addComponent(Args&&... args)
    {
        auto newComponent = std::make_unique<TComponent>(std::forward<Args>(args)...);
        TComponent* ptr = newComponent.get();
        m_components.push_back(std::move(newComponent));
        return ptr;
    }
    Component* addComponent(std::unique_ptr<Component> newComponent)
    {
        Component* ptr = newComponent.get();
        m_components.push_back(std::move(newComponent));
        return ptr;
    }

    template <typename TComponent>
        requires(std::is_base_of_v<Component, TComponent>)
    bool removeComponent()
    {
        auto component = std::ranges::find_if(m_components.begin(), m_components.end(),
            [](const std::unique_ptr<Component>& component)
        {
            return dynamic_cast<TComponent*>(component.get()) != nullptr;
        });

        if (component != m_components.end())
        {
            m_components.erase(component);
            return true;
        }
        return false;
    }

    Scene* getScene() { return m_scene; }

    Entity* getParent() const
    {
        return m_parent;
    }
    const std::vector<Entity*>& getChildren() const
    {
        return m_children;
    }
    void setParent(Entity* parent);

    void markChildrenDirty();

private:
    Core::UUID id;
    Scene* m_scene;

    std::vector<std::unique_ptr<Component>> m_components;

    Entity* m_parent;
    std::vector<Entity*> m_children;

private:
    void addChild(Entity* child);
    void removeChild(Entity* child);
};
}
