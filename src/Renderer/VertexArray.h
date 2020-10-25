#pragma once
#include <vector>
#include <glad/glad.h>

namespace RenderEngine
{
class VertexBuffer;

class VertexBufferLayout
{
public:
    struct VertexBufferLayoutElement
    {
        GLint       countElementsPerVertex;
        GLenum      type;
        GLboolean   normalized;
        GLint       size;
        GLint      offset;
    };

    VertexBufferLayout(unsigned int stride = 0);
    ~VertexBufferLayout();

    VertexBufferLayout(const VertexBufferLayout&) = delete;
    VertexBufferLayout& operator=(const VertexBufferLayout&) = delete;

    VertexBufferLayout(VertexBufferLayout&& other) noexcept;
    VertexBufferLayout& operator=(VertexBufferLayout&& other) noexcept;

    void reserveLayouts(size_t count);
    void addLayoutFloat(GLint countElements, bool normalized, GLint offset = 0);

    int getStride() const { return m_stride; }
    const std::vector<VertexBufferLayoutElement>& getLayoutElements() const { return m_layoutElements; }
private:
    std::vector<VertexBufferLayoutElement> m_layoutElements;
    unsigned int m_stride;
};

class VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    VertexArray(VertexArray&& other) noexcept;
    VertexArray& operator=(VertexArray&& other) noexcept;

    VertexArray(const VertexArray&) = delete;
    VertexArray& operator=(const VertexArray&) = delete;

    void addBuffer(const VertexBuffer& vertBuffer, const VertexBufferLayout& vertLayout);
    void bind() const;
    void unbind() const;

private:
    GLuint m_ID;
    GLuint m_layoutsCount;
};



}
