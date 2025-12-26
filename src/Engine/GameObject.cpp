#include "GameObject.h"
#include <type_traits>

namespace Engine
{
GameObject::GameObject(const std::string& name, GameObject* parent)
    : name(name)
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

glm::mat4 GameObject::getWorldMatrix()
{
    glm::mat4 localMatrix = transform.toMatrix(); // Position/Rot/Scale

    // Recursion: If I have a parent, multiply my matrix by theirs
    if (m_parent != nullptr)
    {
        return m_parent->getWorldMatrix() * localMatrix;
    }

    // If no parent, my Local is my World
    return localMatrix;
}

}
