#include "GameObject.h"
#include "Scene.h"

namespace Engine
{
GameObject::GameObject(const std::string& name, GameObject* parent)
    : id()
    , name(name)
    , m_parent(parent)
{
}

GameObject::GameObject(Core::UUID id, const std::string& name, GameObject* parent)
    : id(id)
    , name(name)
    , m_parent(parent)
{
}

void GameObject::setParent(GameObject* parent)
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
}

void GameObject::markChildrenDirty()
{
    transform->forceSetDirty(); // marks dirty without owner->markChildrenDirty

    for (GameObject* child : m_children)
    {
        child->markChildrenDirty();
    }
}

void GameObject::addChild(GameObject* child)
{
    m_children.push_back(child);
}

void GameObject::removeChild(GameObject* child)
{
    auto it = std::remove(m_children.begin(), m_children.end(), child);
    if (it != m_children.end())
    {
        m_children.erase(it, m_children.end());
    }
}

}
