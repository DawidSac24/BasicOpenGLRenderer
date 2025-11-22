#pragma once

namespace Math
{
class Vector3
{
  public:
    Vector3(float x, float y, float z) : m_x(x), m_y(y), m_z(z)
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
    float getZ()
    {
        return m_z;
    }
    void setZ(float z)
    {
        m_z = z;
    }

  private:
    float m_x, m_y, m_z;
};
} // namespace Math
