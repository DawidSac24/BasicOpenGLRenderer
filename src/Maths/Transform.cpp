#include "Transform.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Math
{
Transform::Transform(glm::vec3 position, glm::quat rotation, glm::vec3 scale)
    : position(position)
    , rotation(rotation)
    , scale(scale)
{
}

glm::mat4 Transform::getModelMatrix()
{
    glm::mat4 identity = glm::mat4(1.0f);

    glm::mat4 translate = glm::translate(identity, position);
    glm::mat4 rotate = glm::mat4_cast(rotation);
    // glm::mat4 scale = glm::scale(identity, scale);

    return translate * rotate /* * scale*/;
}
} // namespace Math
