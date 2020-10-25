#pragma once

#include "glad/glad.h"

namespace Renderer
{
class IndexBuffer
{
public:
    IndexBuffer();
    ~IndexBuffer();

    IndexBuffer(IndexBuffer&& other) noexcept;
    IndexBuffer& operator=(IndexBuffer&& other) noexcept;

    IndexBuffer(const IndexBuffer&) = delete;
    IndexBuffer& operator=(const IndexBuffer&) = delete;

    void init(const void* data, unsigned int size);
    void bind() const;
    void unbind() const;

private:
    GLuint m_ID;
};

}
