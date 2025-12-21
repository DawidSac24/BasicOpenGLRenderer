#pragma once

#include "glm/fwd.hpp"
#include <glm/glm.hpp>

#include <string>
#include <unordered_map>

namespace Renderer
{
class Shader
{
private:
    std::string m_vert_filepath, m_frag_filepath;
    unsigned int m_rendererID;
    std::unordered_map<std::string, int> m_uniformLocationCache;

    std::string parseShader(const std::string& filepath);
    unsigned int createShader(const std::string& vert_shader, const std::string& frag_shader);

    unsigned int compileShader(unsigned int type, const std::string& source);

    int getUniformLocation(const std::string& name);

public:
    Shader(const std::string vert_filepath, std::string frag_filepath);
    ~Shader();

    void bind() const;
    void unbind() const;

    // set uniforms
    void setUniform1i(const std::string& name, int value);
    void setUniform1f(const std::string& name, float value);
    void setUniform3f(const std::string& name, const glm::vec3 values);
    void setUniform4f(const std::string& name, const glm::vec4 values);
    void setUniformMat4f(const std::string& name, const glm::mat4 matrix);
};

//
} // namespace Renderer
