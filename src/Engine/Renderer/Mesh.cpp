#include "Mesh.h"

namespace Renderer
{
Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices)
{
    m_VAO = std::make_unique<VertexArray>();
    m_VBO = std::make_unique<VertexBuffer>(vertices);
    m_IBO = std::make_unique<IndexBuffer>(indices);

    m_VAO->bind();

    VertexBufferLayout layout;
    layout.push<float>(3); // Position
    layout.push<float>(3); // Normal
    layout.push<float>(3); // Color
    layout.push<float>(2); // UV

    m_VAO->addBuffer(*m_VBO, layout);
}

void Mesh::bind() const
{
    m_VAO->bind();
    m_IBO->bind(); // Ensure IBO is bound with VAO
}

int Mesh::getIndexCount() const
{
    return m_IBO->getCount(); // Assuming your IndexBuffer has this
}
} // namespace Engine
