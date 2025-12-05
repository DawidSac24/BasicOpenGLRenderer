#pragma once

#include "Shader.h"
#include "buffers/IndexBuffer.h"
#include "buffers/VertexArray.h"

namespace Renderer
{
class Renderer
{
  public:
    void clear() const;

    void draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader);
};
} // namespace Renderer
