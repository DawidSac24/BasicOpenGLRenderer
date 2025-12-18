#pragma once

#include <glm/gtc/quaternion.hpp>

#include "glm/fwd.hpp"
#include "glm/glm.hpp"

namespace Math {

class Transform {
 public:
  glm::vec3 m_position, m_scale;
  glm::quat m_rotation;

 public:
  Transform(glm::vec3 position, glm::quat rotation, glm::vec3 scale);

  glm::mat4 getModelMatrix();
};
}  // namespace Math
