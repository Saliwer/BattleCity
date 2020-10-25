#pragma once

#include "glad/glad.h"

namespace RenderEngine
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

    void init(const void* data, unsigned int count);
    void bind() const;
    void unbind() const;

    GLuint getCount() const { return m_countElements; }

private:
    GLuint m_ID;
    GLuint m_countElements;
};

}
