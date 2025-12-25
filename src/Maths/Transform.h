#pragma once

#include "glm/fwd.hpp"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Math
{

class Transform
{
public:
    glm::vec3 position;
    glm::quat rotation;
    glm::vec3 scale;

public:
    Transform(glm::vec3 position, glm::quat rotation, glm::vec3 scale);

    glm::mat4 getModelMatrix();
};
} // namespace Math
