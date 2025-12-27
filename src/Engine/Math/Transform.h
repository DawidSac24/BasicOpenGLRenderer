#pragma once

#include "Engine/Scene/Entity.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace Engine
{
class Entity;
}

namespace Math
{

class Transform
{
public:
    Engine::Entity* owner = nullptr;

public:
    Transform() = default;

    glm::vec3 getPosition() const { return m_position; }
    glm::quat getRotation() const { return m_rotation; }
    glm::vec3 getScale() const { return m_scale; }

    glm::mat4 getLocalMatrix() const;
    glm::mat4 getWorldMatrix();

    void setPosition(const glm::vec3& position)
    {
        m_position = position;
        markDirty();
    }
    void setRotation(const glm::quat& rotation)
    {
        m_rotation = rotation;
        markDirty();
    }
    void setScale(const glm::vec3& scale)
    {
        m_scale = scale;
        markDirty();
    }

    void forceSetDirty() { m_isDirty = true; }
    void markDirty();

private:
    glm::vec3 m_position = { 0.0f, 0.0f, 0.0f };
    glm::quat m_rotation = glm::vec3(0.0f, 0.0f, 0.0f); // Identity
    glm::vec3 m_scale = { 1.0f, 1.0f, 1.0f };

    bool m_isDirty = true; // Start dirty to force first calculation
    glm::mat4 m_worldMatrix; // Cached result

private:
    glm::mat4 computeWorldMatrix();
};
} // namespace Math
