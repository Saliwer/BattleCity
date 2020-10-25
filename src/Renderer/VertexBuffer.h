#pragma once

#include "glad/glad.h"

namespace Renderer
{
class VertexBuffer
{
public:
    VertexBuffer();
    ~VertexBuffer();

    VertexBuffer(VertexBuffer&& other) noexcept;
    VertexBuffer& operator=(VertexBuffer&& other) noexcept;

    VertexBuffer(const VertexBuffer&) = delete;
    VertexBuffer& operator=(const VertexBuffer&) = delete;

    void init(const void* data, unsigned int size);
    void update(const void* data, unsigned int size, GLintptr offset = 0) const;
    void bind() const;
    void unbind() const;

private:
    GLuint m_ID;
};

}
