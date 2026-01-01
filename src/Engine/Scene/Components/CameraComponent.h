#pragma once

#include "Engine/Scene/Components/Component.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Engine
{

class Entity;

class CameraComponent : public Component
{
public:
    float fov = 45.0f;
    float nearClip = 0.1f;
    float farClip = 100.0f;
    float aspectRatio = 1.778f; // 16:9 default
public:
    CameraComponent(Entity* owner)
        : Component(owner)
    {
    }

    glm::mat4 getProjection() const { return glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip); }

    void setViewportSize(uint32_t width, uint32_t height)
    {
        if (height > 0)
            aspectRatio = (float)width / (float)height;
    }

    bool isPrimary() const { return m_isPrimary; }
    void setIsPrimary(const bool value) { m_isPrimary = value; }

private:
    bool m_isPrimary = false;
};

}
