#pragma once

#include <memory>
#include <vector>

#include "Texture.h"
#include "buffers/IndexBuffer.h"
#include "buffers/VertexArray.h"

namespace Renderer
{
class Mesh
{
private:
    std::unique_ptr<VertexArray> m_VAO;
    std::unique_ptr<VertexBuffer> m_VBO;
    std::unique_ptr<IndexBuffer> m_IBO;

public:
    Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices);

    void bind() const;

    int getIndexCount() const;
};
} // namespace Engine
