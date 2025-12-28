#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace Engine
{

class EditorCamera
{
public:
    EditorCamera(float fov, float aspectRatio, float nearClip, float farClip)
        : m_FOV(fov)
        , m_AspectRatio(aspectRatio)
        , m_NearClip(nearClip)
        , m_FarClip(farClip)
    {
        updateView();
    }

    void onUpdate(float dt);
    void onEvent(class Event& e);

    // --- The Interface the Renderer needs ---
    const glm::mat4& getViewMatrix() const { return m_ViewMatrix; }
    glm::mat4 getProjection() const
    {
        return glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearClip, m_FarClip);
    }
    glm::mat4 getViewProjection() const { return getProjection() * m_ViewMatrix; }

    // Helpers for Editor Movement
    void setViewportSize(float width, float height)
    {
        if (height == 0)
            return;
        m_AspectRatio = width / height;
    }

    glm::vec3 getPosition() const { return m_Position; }

private:
    void updateView()
    {
        // Recalculate View Matrix based on m_Position and m_Rotation (Pitch/Yaw)
        // (Simple LookAt or Euler angle math goes here)
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position)
            * glm::rotate(glm::mat4(1.0f), m_Pitch, { 1, 0, 0 }) * glm::rotate(glm::mat4(1.0f), m_Yaw, { 0, 1, 0 });

        m_ViewMatrix = glm::inverse(transform);
    }

    float m_FOV, m_AspectRatio, m_NearClip, m_FarClip;
    glm::mat4 m_ViewMatrix;
    glm::vec3 m_Position = { 0.0f, 0.0f, 5.0f };

    // Editor Camera specific vars
    float m_Pitch = 0.0f, m_Yaw = 0.0f;
};

}