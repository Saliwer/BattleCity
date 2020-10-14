#include "Texture2D.h"

namespace Renderer{

Texture2D::Texture2D(int width, int height, int channels, unsigned char* data,
                    GLenum wrap, GLenum filter) : m_width(width), m_height (height)
{
    glGenTextures(1, &m_ID);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);

    switch(channels)
    {
    case 3:
        m_mode = GL_RGB;
        break;
    case 4:
        m_mode = GL_RGBA;
        break;
    default:
        m_mode = GL_RGBA;
        break;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, m_mode, m_width, m_height, 0, m_mode, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture2D::~Texture2D()
{
    glDeleteTextures(1, &m_ID);
}

Texture2D::Texture2D(Texture2D&& other) noexcept
{
    m_ID = other.m_ID;
    m_mode = other.m_mode;
    m_width = other.m_width;
    m_height = other.m_height;
    other.m_ID = 0;
}

Texture2D& Texture2D::operator=(Texture2D&& other) noexcept
{
    glDeleteTextures(1, &m_ID);
    m_ID = other.m_ID;
    m_mode = other.m_mode;
    m_width = other.m_width;
    m_height = other.m_height;
    other.m_ID = 0;
    return *this;
}

void Texture2D::bind() const
{
    if (m_ID)
        glBindTexture(GL_TEXTURE_2D, m_ID);
}

void Texture2D::unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

}
