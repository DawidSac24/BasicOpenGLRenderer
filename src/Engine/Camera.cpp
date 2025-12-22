#include "Camera.h"
#include "GL/glew.h"
#include "glm/gtc/type_ptr.hpp"

namespace Engine
{
Camera::Camera(float width, float height, glm::vec3 initialPosition)
    : transform({ initialPosition, glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(1.0f) })
    , m_fov(45.0f)
    , m_aspect(width / height)
    , m_near(0.1f)
    , m_far(100.0f)
{
    // Initialize matrices to identity
    m_view = glm::mat4(1.0f);
    m_projection = glm::mat4(1.0f);
}

void Camera::matrix(Renderer::Shader& shader, const char* uniform)
{
    //  Calculate Projection (The Lens)
    m_projection = glm::perspective(glm::radians(m_fov), m_aspect, m_near, m_far);

    //  Calculate View (The Position/Rotation)
    //  The camera's "Model Matrix" is where it is in the world.
    //  The "View Matrix" is the opposite of that./
    glm::mat4 cameraModel = transform.getModelMatrix();
    m_view = glm::inverse(cameraModel);

    // 3. Send to Shader
    // If your shader uses separate matrices (u_View, u_Projection):
    // use Mat4f with simple reference for now, may need to pass by glm::valueptr()
    shader.setUniformMat4f("u_view", m_view);
    shader.setUniformMat4f("u_rojection", m_projection);

    // OR if your shader combines them into one "camMatrix" (like in your snippet):
    // glm::mat4 result = m_projection * m_view;
    // glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(result));
}
}
