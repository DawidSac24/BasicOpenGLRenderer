#pragma once

#include <string>
#include <unordered_map>

namespace Renderer
{
class Shader
{
  private:
    std::string m_vert_filepath, m_frag_filepath;
    unsigned int m_rendererID;

    std::string parseShader(const std::string &filepath);
    unsigned int createShader(const std::string &vert_shader, const std::string &frag_shader);

    unsigned int compileShader(unsigned int type, const std::string &source);

    int getUniformLocation(const std::string &name);

  public:
    Shader(const std::string vert_filepath, std::string frag_filepath);
    ~Shader();

    void bind() const;
    void unbind() const;

    // set uniforms
    void setUniform4f(const std::string &name, float v0, float v1, float v2, float v3);
};

//
} // namespace Renderer
