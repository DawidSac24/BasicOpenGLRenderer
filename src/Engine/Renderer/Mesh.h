#pragma once

#include <memory>
#include <vector>

#include "buffers/IndexBuffer.h"
#include "buffers/VertexArray.h"

namespace Renderer
{
class Mesh
{
public:
    Mesh(const std::string& name, std::vector<Vertex>& vertices, std::vector<GLuint>& indices);

    void bind() const;

    int getIndexCount() const;
    VertexArray* getVAO() { return m_VAO.get(); }
    VertexBuffer* getVBO() { return m_VBO.get(); }
    IndexBuffer* getIBO() { return m_IBO.get(); }

    const std::string& getName() const { return m_name; }
    const std::string& getFilepath() const { return m_filepath; }
    void setFilepath(const std::string& filepath) { m_filepath = filepath; }

private:
    std::string m_name;
    std::string m_filepath;

    std::unique_ptr<VertexArray> m_VAO;
    std::unique_ptr<VertexBuffer> m_VBO;
    std::unique_ptr<IndexBuffer> m_IBO;
};
} // namespace Engine
