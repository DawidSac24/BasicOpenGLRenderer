#pragma once

#include <memory>
#include <vector>

#include "Engine/Camera.h"
#include "Renderer/Renderer.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include "Renderer/buffers/IndexBuffer.h"
#include "Renderer/buffers/VertexArray.h"

namespace Engine
{
class Mesh
{
private:
    std::vector<Renderer::Vertex> m_vertices;
    std::vector<GLuint> m_indices;
    std::vector<Renderer::Texture> m_textures;

    std::unique_ptr<Renderer::VertexArray> m_VAO;
    std::unique_ptr<Renderer::VertexBuffer> m_VBO;
    std::unique_ptr<Renderer::IndexBuffer> m_IBO;

public:
    Mesh(std::vector<Renderer::Vertex>& vertices, std::vector<GLuint>& indices,
        std::vector<Renderer::Texture>& textures);

    void draw(Renderer::Renderer& renderer, Renderer::Shader& shader);
};
} // namespace Engine
