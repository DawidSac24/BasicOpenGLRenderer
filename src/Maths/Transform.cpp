#include "Transform.h"

namespace Math
{
Transform::Transform(glm::vec3 position, glm::quat rotation, glm::vec3 scale)
    : m_position(position)
    , m_rotation(rotation)
    , m_scale(scale)
{
}

glm::mat4 Transform::getModelMatrix()
{
    glm::mat4 identity = glm::mat4(1.0f);

    glm::mat4 translate = glm::translate(identity, m_position);
    glm::mat4 rotate = glm::mat4_cast(m_rotation);
    glm::mat4 scale = glm::scale(identity, m_scale);

    return translate * rotate * scale;
}
} // namespace Math
