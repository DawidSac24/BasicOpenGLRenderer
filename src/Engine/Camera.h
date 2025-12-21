#pragma once

#include "Maths/Transform.h"

#include "glm/fwd.hpp"

namespace Engine
{
class Camera
{
private:
    Math::Transform m_transform;

    glm::mat4 m_view;
    glm::mat4 m_projection;

    float m_fov = 45.0f;
    float m_near = 0.1f;
    float m_far = 100.0f;

public:
    Camera(float width, float height, glm::vec3 initialPosition);

    void UpdateMatrix(float width, float height);

    const glm::mat4& GetViewMatrix() const { return m_view; }
    const glm::mat4& GetProjectionMatrix() const { return m_projection; }

    Math::Transform& GetTransform() { return m_transform; }
};
}
