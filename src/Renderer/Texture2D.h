#pragma once

#include "glad/glad.h"
#include <string>

namespace Renderer{

class Texture2D{
public:
    Texture2D(int width, int height, int channels, unsigned char* data,
              GLenum wrap = GL_CLAMP_TO_EDGE, GLenum filter = GL_LINEAR);
    ~Texture2D();
    Texture2D(Texture2D&& other) noexcept;
    Texture2D& operator=(Texture2D&& other) noexcept;

    Texture2D(const Texture2D&) = delete;
    Texture2D& operator=(const Texture2D&) = delete;

    void bind() const;
    void unbind() const;

private:
    int    m_width;
    int    m_height;
    GLuint m_ID;
    GLenum m_mode;
};


}
