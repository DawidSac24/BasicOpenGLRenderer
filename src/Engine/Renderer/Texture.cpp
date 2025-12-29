#include "Texture.h"

#include "Engine/Core/FileSystem.h"
#include "buffers/VertexBufferLayout.h"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Renderer
{
Texture::Texture(const std::string& path, const char* type)
    : m_rendererId(0)
    , type(type)
    , m_filepath(path)
    , m_width(0)
    , m_height(0)
    , m_BPP(0)
{
    // 1. Resolve Path (Consistency with Shader)
    std::string fullPath = Core::FileSystem::getPath(path);

    glGenTextures(1, &m_rendererId);
    glBindTexture(GL_TEXTURE_2D, m_rendererId);

    stbi_set_flip_vertically_on_load(1);

    // 2. Use a local variable, not a member, since we free it immediately
    unsigned char* localBuffer = stbi_load(fullPath.c_str(), &m_width, &m_height, &m_BPP, 4);

    if (!localBuffer)
    {
        std::cout << "Failed to load texture: " << fullPath << std::endl;
    }

    // 3. Texture Parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // 4. Upload
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);
    glBindTexture(GL_TEXTURE_2D, 0);

    // 5. Free memory
    if (localBuffer)
        stbi_image_free(localBuffer);
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
