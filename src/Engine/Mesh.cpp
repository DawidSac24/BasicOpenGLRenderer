#include "Mesh.h"

#include "Renderer/Renderer.h"
#include "Renderer/buffers/IndexBuffer.h"
#include "Renderer/buffers/VertexArray.h"
#include "Renderer/buffers/VertexBuffer.h"
#include "Renderer/buffers/VertexBufferLayout.h"
#include <memory>

namespace Engine
{
Mesh::Mesh(
    std::vector<Renderer::Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Renderer::Texture>& textures)
{
    m_vertices = vertices;
    m_indices = indices;
    m_textures = textures;

    m_VAO = std::make_unique<Renderer::VertexArray>();
    m_VBO = std::make_unique<Renderer::VertexBuffer>(vertices);
    m_IBO = std::make_unique<Renderer::IndexBuffer>(indices);

    m_VAO->bind();

    Renderer::VertexBufferLayout layout;
    layout.push<float>(3); // Position
    layout.push<float>(3); // Normal
    layout.push<float>(3); // Color
    layout.push<float>(2); // UV

    m_VAO->addBuffer(*m_VBO, layout);
}

void Mesh::draw(Renderer::Renderer& renderer, Renderer::Shader& shader, GLenum drawMode)
{
    shader.bind();

    // Keep track of how many of each type of textures we have
    unsigned int numDiffuse = 0;
    unsigned int numSpecular = 0;

    for (unsigned int i = 0; i < m_textures.size(); i++)
    {
        std::string num;
        std::string type = m_textures[i].getType();
        if (type == "diffuse")
        {
            num = std::to_string(numDiffuse++);
        }
        else if (type == "specular")
        {
            num = std::to_string(numSpecular++);
        }
        shader.setUniform1i((type + num).c_str(), i);
        m_textures[i].bind(i);
    }

    renderer.draw(*m_VAO, *m_IBO, shader, drawMode);
}
} // namespace Engine
