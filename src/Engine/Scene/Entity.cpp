#include "Entity.h"

#include "Engine/Scene/Components/TransformComponent.h"
#include "Scene.h"

namespace Engine
{
std::string EntityTypeToString(Engine::EntityType type)
{
    switch (type)
    {
    case Engine::EntityType::Empty:
        return "Empty";
    case Engine::EntityType::Cube:
        return "Cube";
    case Engine::EntityType::Sphere:
        return "Sphere";
    case Engine::EntityType::Plane:
        return "Plane";
    case Engine::EntityType::Camera:
        return "Camera";
    default:
        return "Unknown";
    }
}

Entity::Entity(const std::string& name, Scene* scene, Entity* parent)
    : name(name)
    , id()
    , m_scene(scene)
    , m_parent(parent)
{
    transform = addComponent<TransformComponent>(this);
}

Entity::Entity(Core::UUID id, const std::string& name, Scene* scene, Entity* parent)
    : name(name)
    , id(id)
    , m_scene(scene)
    , m_parent(parent)
{
    transform = addComponent<TransformComponent>(this);
}

void Entity::setParent(Entity* parent)
{
    if (m_parent != nullptr)
    {
        m_parent->removeChild(this);
    }

    m_parent = parent;

    if (m_parent != nullptr)
    {
        m_parent->addChild(this);
    }

    if (transform)
        transform->markDirty();
}

void Entity::markChildrenDirty()
{
    transform->forceSetDirty(); // marks dirty without owner->markChildrenDirty to break the recursion loop

    for (Entity* child : m_children)
    {
        child->markChildrenDirty();
    }
}

void Entity::addChild(Entity* child)
{
    m_children.push_back(child);
}

void Entity::removeChild(Entity* child)
{
    auto it = std::remove(m_children.begin(), m_children.end(), child);
    if (it != m_children.end())
    {
        m_children.erase(it, m_children.end());
    }
}

}
