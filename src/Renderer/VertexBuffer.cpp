#include "VertexBuffer.h"

namespace Renderer
{
VertexBuffer::VertexBuffer() : m_ID(0)
{}

VertexBuffer::~VertexBuffer()
{
    if (!m_ID)
        glDeleteBuffers(1, &m_ID);
}


VertexBuffer::VertexBuffer(VertexBuffer&& other) noexcept
{
    m_ID = other.m_ID;
    other.m_ID = 0;
}

VertexBuffer& VertexBuffer::operator=(VertexBuffer&& other) noexcept
{
    m_ID = other.m_ID;
    other.m_ID = 0;
    return *this;
}


void VertexBuffer::init(const void* data, unsigned int size)
{
    glGenBuffers(1, &m_ID);
    glBindBuffer(GL_ARRAY_BUFFER, m_ID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void VertexBuffer::update(const void* data, unsigned int size, GLintptr offset) const
{
    bind();
    glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}

void VertexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}

void VertexBuffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


}
