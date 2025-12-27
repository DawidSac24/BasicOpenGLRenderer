#include "Entity.h"

#include "Engine/Math/Transform.h"
#include "Scene.h"

namespace Engine
{
Entity::Entity(const std::string* name, Entity* parent)
    : id()
    , m_parent(parent)
{
    if (name)
        this->name = *name;

    transform = std::make_unique<Math::Transform>();
    transform->owner = this;
}

Entity::Entity(Core::UUID id, const std::string* name, Entity* parent)
    : id(id)
    , m_parent(parent)
{
    if (name)
        this->name = *name;

    transform = std::make_unique<Math::Transform>();
    transform->owner = this;
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
