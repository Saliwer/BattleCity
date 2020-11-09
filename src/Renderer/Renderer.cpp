#include "Renderer.h"

namespace RenderEngine
{
void Renderer::draw(const VertexArray& vertArray, const IndexBuffer& iBufffer,
                    const ShaderProgram& shader)
{
    shader.use();
    vertArray.bind();
    glDrawElements(GL_TRIANGLES, iBufffer.getCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::clear(GLbitfield bits)
{
    glClear(bits);
}

void Renderer::setClearColor(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
}

void Renderer::setViewport(unsigned int width, unsigned int height,
                            unsigned int rightOffset, unsigned int topOffset)
{
    glViewport(rightOffset, topOffset, width, height);
}
void Renderer::setDepthTest(bool flag)
{
    flag ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
}

}
