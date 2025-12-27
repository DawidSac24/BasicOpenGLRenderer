#pragma once

#include "Engine/Math/Transform.h"
#include "Engine/Renderer/Shader.h"

#include "glm/fwd.hpp"

namespace Renderer
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

    void updateDimensions(float width, float height) { m_aspect = width / height; }

    const glm::mat4& getViewMatrix()
    {
        glm::mat4 cameraModel = transform.getWorldMatrix();
        m_view = glm::inverse(cameraModel);
        return m_view;
    }

    const glm::mat4& getProjectionMatrix()
    {
        m_projection = glm::perspective(glm::radians(m_fov), m_aspect, m_near, m_far);
        return m_projection;
    }

    // This is the golden ticket for the Renderer
    glm::mat4 getViewProjection() { return getProjectionMatrix() * getViewMatrix(); }

    void setViewportSize(float width, float height);
};
}
