#include "Sprite.h"
#include "ShaderProgram.h"
#include "Texture2D.h"

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Renderer
{

Sprite::Sprite(std::shared_ptr<ShaderProgram> pShaderProg,
               std::shared_ptr<Texture2D> pTexture,
               const std::string& subTextureName,
               const glm::vec2& position,
               const glm::vec2& size,
               float rotation)
               : m_pShaderProg(std::move(pShaderProg)),
                 m_pTexture(std::move(pTexture)),
                 m_subTextureName(subTextureName),
                 m_position(position), m_size(size),
                 m_rotation(rotation)
{

    const SubTexture& subTexture = m_pTexture->getSubTexture(m_subTextureName);

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

void Sprite::render()
{
    m_pShaderProg->use();
    glm::mat4 modelMatrix = glm::mat4(1.f);

    modelMatrix = glm::translate(modelMatrix, glm::vec3(m_position, 0.f));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0.5f * m_size.x, 0.5f * m_size.y, 0.f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(m_rotation), glm::vec3(0.f, 0.f, 1.f));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.5f * m_size.x, -0.5f * m_size.y, 0.f));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(m_size, 1.f));

    m_vertexArray.bind();
    glActiveTexture(GL_TEXTURE0);


    m_pTexture->bind();
    m_pShaderProg->setUniform("modelMatrix", modelMatrix);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    m_pShaderProg->unUse();
    m_pTexture->unbind();
    m_vertexArray.unbind();

}

void Sprite::setSubTexture(const std::string& name)
{
    m_subTextureName = name;
    changeTextureCoord(m_pTexture->getSubTexture(m_subTextureName));
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
