#pragma once

#include "Shader.h"
#include "Texture.h"
#include <glm/glm.hpp>
#include <memory>
#include <string>
#include <unordered_map>

namespace Renderer
{

class Material
{
public:
    Material(std::string& name, std::shared_ptr<Shader> shader)
        : m_name(name)
        , m_Shader(shader)
    {
    }
    std::unordered_map<std::string, glm::vec4>& getUniforms() { return m_UniformsFloat4; }
    std::unordered_map<std::string, std::shared_ptr<Texture>>& getTextures() { return m_Textures; }

    void setTexture(const std::string& name, std::shared_ptr<Texture> texture) { m_Textures[name] = texture; }

    void setFloat4(const std::string& name, const glm::vec4& value) { m_UniformsFloat4[name] = value; }

    void bind()
    {
        m_Shader->bind();

        // Bind all generic uniforms (Colors, etc.)
        for (auto& [name, value] : m_UniformsFloat4)
        {
            m_Shader->setUniform4f(name, value);
        }

        // Bind Textures
        int slot = 0;
        for (auto& [name, texture] : m_Textures)
        {
            if (texture)
            {
                texture->bind(slot);
                m_Shader->setUniform1i(name, slot);
                slot++;
            }
        }
    }

    const std::string& getName() const { return m_name; }
    const std::string& getFilepath() const { return m_filepath; }
    void setFilepath(const std::string& filepath) { m_filepath = filepath; }

    std::shared_ptr<Shader> getShader() { return m_Shader; }

private:
    std::string m_name;
    std::string m_filepath;

    std::shared_ptr<Shader> m_Shader;

    std::unordered_map<std::string, std::shared_ptr<Texture>> m_Textures;
    std::unordered_map<std::string, glm::vec4> m_UniformsFloat4;
};

}
