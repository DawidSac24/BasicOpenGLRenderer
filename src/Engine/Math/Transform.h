#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace Engine
{
class Entity;
}

namespace Math
{

class Transform
{
public:
    glm::vec3 position = { 0.0f, 0.0f, 0.0f };
    glm::quat rotation = glm::vec3(0.0f, 0.0f, 0.0f); // Identity
    glm::vec3 scale = { 1.0f, 1.0f, 1.0f };

    Transform() = default;
};
} // namespace Math
