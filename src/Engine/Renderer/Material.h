#include "Shader.h"
#include "Texture.h"
#include <memory>
#include <string>
#include <unordered_map>

namespace Renderer
{
class Material
{
public:
    Material(std::shared_ptr<Shader> shader)
        : m_Shader(shader)
    {
    }

    virtual ~Material() = default;

    void SetColor(const std::string& name, const glm::vec4& color) { m_Colors[name] = color; }

    void SetFloat(const std::string& name, float value) { m_Floats[name] = value; }

    void Bind()
    {
        m_Shader->bind();

        for (auto& [name, color] : m_Colors)
        {
            m_Shader->setUniform4f(name, color);
        }

        for (auto& [name, value] : m_Floats)
        {
            m_Shader->setUniform1f(name, value);
        }
    }

    std::shared_ptr<Shader> getShader() { return m_Shader; }

private:
    std::shared_ptr<Shader> m_Shader;

    std::unordered_map<std::string, glm::vec4> m_Colors;
    std::unordered_map<std::string, float> m_Floats;
};
}
