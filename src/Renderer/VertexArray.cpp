#include "VertexArray.h"
#include "VertexBuffer.h"

namespace RenderEngine
{
VertexBufferLayout::VertexBufferLayout(unsigned int stride) : m_stride(stride)
{}

VertexBufferLayout::~VertexBufferLayout()
{}

VertexBufferLayout::VertexBufferLayout(VertexBufferLayout&& other) noexcept
{
    m_layoutElements = std::move(other.m_layoutElements);
    m_stride = other.m_stride;
}

VertexBufferLayout& VertexBufferLayout::operator=(VertexBufferLayout&& other) noexcept
{
    m_layoutElements.clear();
    m_layoutElements = std::move(other.m_layoutElements);
    m_stride = other.m_stride;
    return *this;
}

void  VertexBufferLayout::reserveLayouts(size_t count)
{
    m_layoutElements.reserve(count);
}

void  VertexBufferLayout::addLayoutFloat(GLint countElements, bool normalized, GLint offset)
{
    m_layoutElements.push_back({countElements, GL_FLOAT, normalized, countElements * (GLint)sizeof(GLfloat), offset});
}

VertexArray::VertexArray() : m_ID(0), m_layoutsCount(0)
{
    glGenVertexArrays(1, &m_ID);
}

VertexArray::~VertexArray()
{
    if (!m_ID)
        glDeleteVertexArrays(1, &m_ID);
}


VertexArray::VertexArray(VertexArray&& other) noexcept
{
    m_ID = other.m_ID;
    m_layoutsCount = other.m_layoutsCount;
    other.m_ID = 0;
    other.m_layoutsCount = 0;
}

VertexArray& VertexArray::operator=(VertexArray&& other) noexcept
{
    m_ID = other.m_ID;
    m_layoutsCount = other.m_layoutsCount;
    other.m_ID = 0;
    other.m_layoutsCount = 0;
    return *this;
}


void VertexArray::addBuffer(const VertexBuffer& vertBuffer, const VertexBufferLayout& vertLayout)
{
    bind();
    vertBuffer.bind();
    const auto& layoutsArr = vertLayout.getLayoutElements();
    for(size_t i = 0; i < layoutsArr.size(); ++i)
    {
        glEnableVertexAttribArray(m_layoutsCount + i);
        glVertexAttribPointer(m_layoutsCount + i, layoutsArr[i].countElementsPerVertex,
                              layoutsArr[i].type, layoutsArr[i].normalized, vertLayout.getStride(),
                              (void*)0);
    }
    m_layoutsCount+=layoutsArr.size();
}

void VertexArray::bind() const
{
    glBindVertexArray(m_ID);
}

void VertexArray::unbind() const
{
    glBindVertexArray(0);
}


}
