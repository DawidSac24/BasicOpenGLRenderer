#pragma once

#include "Component.h"
#include "Engine/Math/Transform.h"

class Entity;

namespace Engine
{
class TransformComponent : public Component
{
public:
    TransformComponent(Entity* owner);

    inline glm::vec3 getPosition() const { return m_handle.position; }
    inline glm::quat getRotation() const { return m_handle.rotation; }
    inline glm::vec3 getScale() const { return m_handle.scale; }

    inline void setPosition(const glm::vec3& position)
    {
        m_handle.position = position;
        markDirty();
    }
    inline void setRotation(const glm::quat& rotation)
    {
        m_handle.rotation = rotation;
        markDirty();
    }
    inline void setScale(const glm::vec3& scale)
    {
        m_handle.scale = scale;
        markDirty();
    }

    void markDirty();
    inline void forceSetDirty() { m_isDirty = true; }

    glm::mat4 getLocalMatrix() const;
    glm::mat4 getWorldMatrix();

private:
    Math::Transform m_handle;

    bool m_isDirty = true; // Start dirty to force first calculation
    glm::mat4 m_worldMatrix; // Cached result

private:
    glm::mat4 computeWorldMatrix();
};
}
