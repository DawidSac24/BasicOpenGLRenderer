#include "Texture.h"
#include <GL/gl.h>

#include "../../vendor/stb_image/stb_image.h"
#include "buffers/VertexBufferLayout.h"
namespace Renderer
{
Texture::Texture(const std::string &path)
    : m_rendererId(0), m_filepath(path), m_localBuffer(nullptr), m_width(0), m_height(0), m_BPP(0)
{
    glGenTextures(1, &m_rendererId);
    glBindTexture(GL_TEXTURE_2D, m_rendererId);

    stbi_set_flip_vertically_on_load(1);
    m_localBuffer = stbi_load(path.c_str(), &m_width, &m_height, &m_BPP, 4);

    glGenTextures(1, &m_rendererId);
    glBindTexture(GL_TEXTURE_2D, m_rendererId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // GL_RGBA8 is to specify internalformat, should add a the number of bits per channel for better practice
    // can pass nullptr to *pixels param, allowing to allocate the memory first
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer);
    glBindTexture(GL_TEXTURE_2D, 0);

    if (m_localBuffer)
        // can be freed after if we want to store or sample it for exemple
        stbi_image_free(m_localBuffer);
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_rendererId);
}

void Texture::bind(unsigned int slot /*= 0*/) const
{
    // can specify a texture slot for opengl (32 being the maximum), varies by platform
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_rendererId);
}

void Texture::unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

} // namespace Renderer
