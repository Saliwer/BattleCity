#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "ShaderProgram.h"

namespace RenderEngine
{
class Renderer
{
public:
    static void draw(const VertexArray& vertArray,
                     const IndexBuffer& iBufffer,
                     const ShaderProgram& shader);

    static void clear(GLbitfield bits);
    static void setClearColor(float r, float g, float b, float a);
    static void setViewport(unsigned int width, unsigned int height,
                            unsigned int rightOffset = 0, unsigned int topOffset = 0);
    static void setDepthTest(bool flag);
};


}
