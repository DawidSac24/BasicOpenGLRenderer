#include "VertexBuffer.h"

#include <GL/glew.h>

namespace Renderer
{
VertexBuffer::VertexBuffer(std::vector<Vertex>& vertices)
{
    glGenBuffers(1, &m_rendererID);
    // binds (select) the buffer to draw on
    glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
}
VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_rendererID);
}

void VertexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
}
void VertexBuffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

}; // namespace Renderer
