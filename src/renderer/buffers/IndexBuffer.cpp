#include "IndexBuffer.h"

#include <GL/glew.h>

namespace Renderer
{

IndexBuffer::IndexBuffer(const unsigned int *data, unsigned int count) : m_count(count)
{
    // Make sure unsigned int is GLuint at runtime ?
    // assert(sizeof(unsigned int) == sizeof(GLuint));
    glGenBuffers(1, &m_rendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &m_rendererID);
}

void IndexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
}

void IndexBuffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

}; // namespace Renderer
