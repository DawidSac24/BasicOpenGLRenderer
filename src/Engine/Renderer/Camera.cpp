#include "Camera.h"

#include "GL/glew.h"

namespace Renderer
{
Camera::Camera(float width, float height, const glm::vec3& initialPosition)
    : transform()
    , m_fov(45.0f)
    , m_aspect(width / height)
    , m_near(0.1f)
    , m_far(100.0f)
{
    transform.setPosition(initialPosition);
    m_view = glm::mat4(1.0f);
    m_projection = glm::mat4(1.0f);
}

glm::mat4 Camera::getMatrix()
{
    //  Calculate Projection (The Lens)
    m_projection = glm::perspective(glm::radians(m_fov), m_aspect, m_near, m_far);

    //  Calculate View (The Position/Rotation)
    //  The camera's "Model Matrix" is where it is in the world.
    //  The "View Matrix" is the opposite of that./
    glm::mat4 cameraModel = transform.getWorldMatrix();
    m_view = glm::inverse(cameraModel);

    // OR if your shader combines them into one "camMatrix" (like in your snippet):
    return m_projection * m_view;
}

void Camera::setViewportSize(float width, float height)
{
    // Guard against minimize (0 divide crash)
    if (width == 0 || height == 0)
        return;

    m_aspect = width / height;

    // If you cache your projection matrix, recalculate it here.
    // If your getMatrix() function calculates it every frame,
    // just updating m_aspect is enough.
    m_projection = glm::perspective(glm::radians(m_fov), m_aspect, m_near, m_far);
}
}
