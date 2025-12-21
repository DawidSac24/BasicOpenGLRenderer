#pragma once

#include "VertexBuffer.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cassert>
#include <vector>

namespace Renderer
{

struct VertexBufferElement
{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int getSizeofType(unsigned int type)
    {
        switch (type)
        {
        case GL_FLOAT:
            return 4;
        case GL_UNSIGNED_INT:
            return 4;
        case GL_UNSIGNED_BYTE:
            return 1;
        }
        assert(false);
        return 0;
    }
};

class VertexBufferLayout
{
private:
    std::vector<VertexBufferElement> m_elements;

    unsigned int m_stride;

public:
    VertexBufferLayout()
        : m_stride(0) { };
    // ~VertexBufferLayout();

    template <typename T> void push(unsigned int count) { static_assert(false); }

    inline const std::vector<VertexBufferElement> getElements() const { return m_elements; }

    inline unsigned int getStride() const { return m_stride; }
};

template <> void VertexBufferLayout::push<float>(unsigned int count);
template <> void VertexBufferLayout::push<unsigned int>(unsigned int count);
template <> void VertexBufferLayout::push<unsigned char>(unsigned int count);

} // namespace Renderer
