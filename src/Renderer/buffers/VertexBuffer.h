#pragma once

#include "glm/glm.hpp"
#include <vector>
namespace Renderer
{

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 color;
    glm::vec2 textUV;
};

class VertexBuffer
{
private:
    unsigned int m_rendererID;

public:
    VertexBuffer(std::vector<Vertex>& vertices);
    ~VertexBuffer();

    void bind() const;
    void unbind() const;
};
}; // namespace Renderer
