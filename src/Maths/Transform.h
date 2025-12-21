#pragma once

#include <glm/gtc/quaternion.hpp>

#include "glm/fwd.hpp"
#include "glm/glm.hpp"

namespace Math
{

class Transform
{
private:
    glm::vec3 m_position;
    glm::quat m_rotation;
    glm::vec3 m_scale;

public:
    Transform(glm::vec3 position, glm::quat rotation, glm::vec3 scale);

    glm::mat4 getModelMatrix();
};
} // namespace Math
