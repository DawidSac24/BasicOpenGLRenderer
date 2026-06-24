#pragma once

#include "Component.h"

#include <glm/fwd.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace Core
{
class ClassDescriptor;
}

class Entity;

namespace Engine
{
class TransformComponent : public Component
{
public:
    glm::vec3 position = { 0.0f, 0.0f, 0.0f };
    glm::quat rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 scale = { 1.0f, 1.0f, 1.0f };

public:
    TransformComponent(Entity* owner);

    void markDirty();
    inline void forceSetDirty() { m_isDirty = true; }

    glm::mat4 getLocalMatrix() const;
    glm::mat4 getWorldMatrix();

    static void registerReflection(Core::ClassDescriptor& desc);

private:
    bool m_isDirty = true; // Start dirty to force first calculation
    glm::mat4 m_worldMatrix; // Cached result

private:
    glm::mat4 computeWorldMatrix();
};
}
