#include "IndexBuffer.h"


namespace RenderEngine
{
IndexBuffer::IndexBuffer() : m_ID(0), m_countElements(0)
{}

IndexBuffer::~IndexBuffer()
{
    if (!m_ID)
        glDeleteBuffers(1, &m_ID);
}


IndexBuffer::IndexBuffer(IndexBuffer&& other) noexcept
{
    m_ID = other.m_ID;
    m_countElements = other.m_countElements;
    other.m_countElements = 0;
    other.m_ID = 0;
}

IndexBuffer& IndexBuffer::operator=(IndexBuffer&& other) noexcept
{
    m_ID = other.m_ID;
    m_countElements = other.m_countElements;
    other.m_countElements = 0;
    other.m_ID = 0;
    return *this;
}


void IndexBuffer::init(const void* data, unsigned int count)
{
    m_countElements = count;
    glGenBuffers(1, &m_ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_countElements * sizeof(GLuint), data, GL_STATIC_DRAW);
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
