#include "Camera.h"
#include "GL/glew.h"

namespace Engine
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

void Camera::matrix(Renderer::Shader& shader, const char* uniform_name)
{
    //  Calculate Projection (The Lens)
    m_projection = glm::perspective(glm::radians(m_fov), m_aspect, m_near, m_far);

    //  Calculate View (The Position/Rotation)
    //  The camera's "Model Matrix" is where it is in the world.
    //  The "View Matrix" is the opposite of that./
    glm::mat4 cameraModel = transform.getWorldMatrix();
    m_view = glm::inverse(cameraModel);

    // OR if your shader combines them into one "camMatrix" (like in your snippet):
    glm::mat4 result = m_projection * m_view;
    shader.setUniformMat4f(uniform_name, result);
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
}
