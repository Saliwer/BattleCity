#include "IndexBuffer.h"


namespace Renderer
{
IndexBuffer::IndexBuffer() : m_ID(0)
{}

IndexBuffer::~IndexBuffer()
{
    if (!m_ID)
        glDeleteBuffers(1, &m_ID);
}


IndexBuffer::IndexBuffer(IndexBuffer&& other) noexcept
{
    m_ID = other.m_ID;
    other.m_ID = 0;
}

IndexBuffer& IndexBuffer::operator=(IndexBuffer&& other) noexcept
{
    m_ID = other.m_ID;
    other.m_ID = 0;
    return *this;
}


void IndexBuffer::init(const void* data, unsigned int size)
{
    glGenBuffers(1, &m_ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void IndexBuffer::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
}

void IndexBuffer::unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


}
