#pragma once

#include "Engine/Maths/Transform.h"
#include "Engine/Renderer/Shader.h"

#include "glm/fwd.hpp"

namespace Engine
{
class Camera
{
private:
    glm::mat4 m_view;
    glm::mat4 m_projection;

    float m_fov;
    float m_aspect;
    float m_near;
    float m_far;

public:
    Math::Transform transform;

public:
    Camera(float width, float height, const glm::vec3& initialPosition);

    glm::mat4 getMatrix();
    void matrix(Renderer::Shader& shader, const char* uniform);

    void updateDimensions(float width, float height) { m_aspect = width / height; }
};
}
