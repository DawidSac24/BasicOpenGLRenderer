#include "Shader.h"

#include <GL/glew.h>
#include <fstream>
#include <glm/glm.hpp>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
namespace Renderer
{
Shader::Shader(const std::string vert_filepath, std::string frag_filepath)
    : m_vert_filepath(vert_filepath)
    , m_frag_filepath(frag_filepath)
    , m_rendererID(0)
{
    std::string vert_source = parseShader(vert_filepath);
    std::string frag_source = parseShader(frag_filepath);

    m_rendererID = createShader(vert_source, frag_source);
}

Shader::~Shader()
{
    glDeleteProgram(m_rendererID);
}

void Shader::bind() const
{
    glUseProgram(m_rendererID);
}

void Shader::unbind() const
{
    glUseProgram(m_rendererID);
}

std::string Shader::parseShader(const std::string& filepath)
{
    std::fstream stream(filepath);

    std::stringstream result;
    std::string line;

    while (std::getline(stream, line))
    {
        result << line << "\n";
    }
    return result.str();
}

unsigned int Shader::createShader(const std::string& vert_shader, const std::string& frag_shader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vert_shader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, frag_shader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

unsigned int Shader::compileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char message[length];
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader"
                  << std::endl;
        std::cout << message << std::endl;

        glDeleteShader(id);
        return 0;
    }

    return id;
}

int Shader::getUniformLocation(const std::string& name)
{
    if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
    {
        return m_uniformLocationCache[name];
    }

    int location = glGetUniformLocation(m_rendererID, name.c_str());
    if (location == -1)
        std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;

    m_uniformLocationCache[name] = location;
    return location;
}

void Shader::setUniform1i(const std::string& name, int value)
{
    glUniform1i(getUniformLocation(name), value);
}

void Shader::setUniform1f(const std::string& name, float value)
{
    glUniform1f(getUniformLocation(name), value);
}

void Shader::setUniform4f(const std::string& name, const glm::vec4 values)
{
    glUniform4f(getUniformLocation(name), values.x, values.y, values.z, values.w);
}

void Shader::setUniformMat4f(const std::string& name, glm::mat4 matrix)
{
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}

} // namespace Renderer
