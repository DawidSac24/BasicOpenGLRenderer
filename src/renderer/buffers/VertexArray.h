#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace Renderer
{
class VertexArray
{
  private:
    unsigned int m_rendererID;

  public:
    VertexArray();
    ~VertexArray();

    void addBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout);

    void bind() const;
    void unbind() const;
};
} // namespace Renderer
