#pragma once

namespace Math
{
class Vector2
{
  public:
    Vector2(float x, float y) : m_x(x), m_y(y)
    {
    }

    float getX()
    {
        return m_x;
    }
    void setX(float x)
    {
        m_x = x;
    }
    float getY()
    {
        return m_y;
    }
    void setY(float y)
    {
        m_y = y;
    }

  private:
    float m_x, m_y;
};
} // namespace Math
