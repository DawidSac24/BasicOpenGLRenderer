#include "Mesh.h"

#include "Renderer/buffers/IndexBuffer.h"
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

    m_VAO->bind();
    m_VBO = std::make_unique<Renderer::VertexBuffer>(vertices);
    m_IBO = std::make_unique<Renderer::IndexBuffer>(indices);

    Renderer::VertexBufferLayout layout;
    layout.push<float>(3); // Position
    layout.push<float>(3); // Normal
    layout.push<float>(3); // Color
    layout.push<float>(2); // UV

    m_VAO->addBuffer(*m_VBO, layout);
}

void Mesh::draw(Renderer::Shader& shader, Camera& camera)
{
    shader.bind();
    m_VAO->bind();
    m_VBO->bind();
    m_IBO->bind();

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
    // Take care of the camera Matrix
    glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
    camera.Matrix(shader, "camMatrix");

    // Draw the actual mesh
    glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);

    m_VAO->unbind();
}
} // namespace Engine
