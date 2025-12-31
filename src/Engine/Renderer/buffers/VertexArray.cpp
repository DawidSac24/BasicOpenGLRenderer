#include "VertexArray.h"

namespace Renderer
{

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &m_rendererID);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_rendererID);
}

void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
    bind();
    vb.bind();
    const auto& elements = layout.getElements();
    unsigned int offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++)
    {
        const auto& element = elements[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(
            i, element.count, element.type, element.normalized, layout.getStride(), (const void*)(uintptr_t)offset);
        offset += element.count * VertexBufferElement::getSizeofType(element.type);
    }
    vb.unbind();
}

void VertexArray::bind() const
{
    glBindVertexArray(m_rendererID);
}

void VertexArray::unbind() const
{
    glBindVertexArray(0);
}
template <>
void VertexBufferLayout::push<float>(unsigned int count)
{
    m_elements.push_back({ GL_FLOAT, count, GL_FALSE });
    m_stride += count * VertexBufferElement::getSizeofType(GL_FLOAT);
}

template <>
void VertexBufferLayout::push<unsigned int>(unsigned int count)
{
    m_elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
    m_stride += count * VertexBufferElement::getSizeofType(GL_UNSIGNED_INT);
}

template <>
void VertexBufferLayout::push<unsigned char>(unsigned int count)
{
    m_elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
    m_stride += count * VertexBufferElement::getSizeofType(GL_UNSIGNED_BYTE);
}
} // namespace Renderer
