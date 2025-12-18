#pragma once

#include "glm/glm.hpp"

namespace Math {

class Transform {
 private:
  glm::vec3 m_position;
  glm::vec2 m_rotation;
  float m_scale;

 public:
  Transform(glm::vec3 position, glm::vec2 rotation, float scale);

  glm::vec3 getPosition() { return m_position; }
  glm::vec2 getRotation() { return m_rotation; }
  float getScale() { return m_scale; }

  void setPosition(glm::vec3 position) { m_position = position; }
  void setRotation(glm::vec2 rotation) { m_rotation = rotation; }
  void setScale(float scale) { m_scale = scale; }
};
}  // namespace Math
