#include "Transform.h"

#include "Engine/Scene/GameObject.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Math
{

void Transform::markDirty()
{
    if (m_isDirty)
        return;

    m_isDirty = true;

    if (owner)
        owner->markChildrenDirty();
}

glm::mat4 Transform::getLocalMatrix() const
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, m_position);
    model *= glm::toMat4(m_rotation);
    model = glm::scale(model, m_scale);
    return model;
}

glm::mat4 Transform::getWorldMatrix()
{
    if (m_isDirty)
    {
        m_worldMatrix = computeWorldMatrix();
        m_isDirty = false;
    }
    return m_worldMatrix;
}

glm::mat4 Transform::computeWorldMatrix()
{
    glm::mat4 localMat = getLocalMatrix();

    if (owner && owner->getParent())
    {
        return owner->getParent()->transform->getWorldMatrix() * localMat;
    }

    return localMat;
}
} // namespace Math
