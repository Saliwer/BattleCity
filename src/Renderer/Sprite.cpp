#include "Sprite.h"
#include "ShaderProgram.h"
#include "Renderer.h"
#include "Texture2D.h"

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/vector_angle.hpp>

namespace RenderEngine
{

Sprite::Sprite(std::shared_ptr<ShaderProgram> pShaderProg,
               std::shared_ptr<Texture2D> pTexture,
               std::string subTextureName)
               : m_pShaderProg(std::move(pShaderProg))
               , m_pTexture(std::move(pTexture))
               , m_activeSubTexture(std::move(subTextureName))
{
    const SubTexture& subTexture = m_pTexture->getSubTexture(m_activeSubTexture);

    GLfloat vertexData[] =
    {
        //vertices
        //X   Y
        0.f,  0.f,
        1.f,  0.f,
        1.f,  1.f,
        0.f,  1.f
    };

    GLfloat textureCoords[] =
    {
        //texture
        //U                         V
        subTexture.leftBottomUV.x,  subTexture.leftBottomUV.y,
        subTexture.rightTopUV.x,    subTexture.leftBottomUV.y,
        subTexture.rightTopUV.x,    subTexture.rightTopUV.y,
        subTexture.leftBottomUV.x,  subTexture.rightTopUV.y
    };

    GLuint indices[] =
    {
        0, 1, 2,
        2, 3, 0
    };

    m_vertexCoords.init(vertexData, 2 * 4 *sizeof(GLfloat));
    m_textureCoords.init(textureCoords, 2 * 4 * sizeof(GLfloat));

    VertexBufferLayout vertexLayout;
    vertexLayout.addLayoutFloat(2, false);
    m_vertexArray.addBuffer(m_vertexCoords, vertexLayout);


    VertexBufferLayout textureLayout;
    textureLayout.addLayoutFloat(2, false);
    m_vertexArray.addBuffer(m_textureCoords, textureLayout);

    m_indices.init(indices, 6 * sizeof(GLuint));

    glBindVertexArray(0);
    m_textureCoords.unbind();
    m_indices.unbind();
}


Sprite::~Sprite()
{
}

void Sprite::render(const glm::vec2& position, const glm::vec2& size, const glm::vec2& direction, float layer) const
{
    m_pShaderProg->use();
    glm::mat4 modelMatrix = glm::mat4(1.f);

    modelMatrix = glm::translate(modelMatrix, glm::vec3(position.x, position.y, layer));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.f));
    modelMatrix = glm::rotate(modelMatrix, glm::orientedAngle(glm::vec2(1.f, 0.f), direction), glm::vec3(0.f, 0.f, 1.f));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.f));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(size, 1.f));

    m_vertexArray.bind();
    glActiveTexture(GL_TEXTURE0);


    m_pTexture->bind();
    m_pShaderProg->setUniform("modelMatrix", modelMatrix);

    RenderEngine::Renderer::draw(m_vertexArray, m_indices, *m_pShaderProg);
}

void Sprite::setSubTexture(const std::string& name)
{
    m_activeSubTexture = name;
    changeTextureCoord(m_pTexture->getSubTexture(m_activeSubTexture));
}

void Sprite::changeTextureCoord(const SubTexture& newCoords)
{
    GLfloat vertexData[] =
    {
        //texture
        //U                        V
        newCoords.leftBottomUV.x,  newCoords.leftBottomUV.y,
        newCoords.rightTopUV.x,    newCoords.leftBottomUV.y,
        newCoords.rightTopUV.x,    newCoords.rightTopUV.y,
        newCoords.leftBottomUV.x,  newCoords.rightTopUV.y,
    };

    m_textureCoords.update(vertexData, 2 * 4 * sizeof(GLfloat));
}

}
