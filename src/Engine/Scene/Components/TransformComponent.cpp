#include "TransformComponent.h"

#include "Engine/Core/Reflection/ClassDescriptor.h"
#include "Engine/Core/Reflection/Registry.h"
#include "Engine/Scene/Components/Component.h"
#include "Engine/Scene/Entity.h"

namespace Engine
{
TransformComponent::TransformComponent(Entity* owner)
    : Component(owner)
{
}

void TransformComponent::markDirty()
{
    if (m_isDirty)
        return;

    m_isDirty = true;

    if (owner)
        owner->markChildrenDirty();
}

glm::mat4 TransformComponent::getLocalMatrix() const
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model *= glm::toMat4(rotation);
    model = glm::scale(model, scale);
    return model;
}

glm::mat4 TransformComponent::getWorldMatrix()
{
    if (m_isDirty)
    {
        m_worldMatrix = computeWorldMatrix();
        m_isDirty = false;
    }
    return m_worldMatrix;
}

glm::mat4 TransformComponent::computeWorldMatrix()
{
    glm::mat4 localMat = getLocalMatrix();

    if (owner && owner->getParent())
    {
        return owner->getParent()->transform->getWorldMatrix() * localMat;
    }

    return localMat;
}

void TransformComponent::registerReflection(Core::ClassDescriptor& desc)
{
    desc.addProperty("position", &TransformComponent::position);
    desc.addProperty("rotation", &TransformComponent::rotation);
    desc.addProperty("scale", &TransformComponent::scale);
}

REFLECT_CLASS(TransformComponent)
}
