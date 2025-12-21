#pragma once

#include <GL/glew.h>
#include <vector>
namespace Renderer
{

class IndexBuffer
{
private:
    unsigned int m_rendererID;

public:
    IndexBuffer(std::vector<GLuint>& indices);
    ~IndexBuffer();

    void bind() const;
    void unbind() const;
};
}; // namespace Renderer
