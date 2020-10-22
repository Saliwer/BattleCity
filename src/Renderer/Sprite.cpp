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
                 m_position(position), m_size(size),
                 m_rotation(rotation),
                 m_VBO(0), m_VAO(0)
{

    const Texture2D::SubTexture& subTexture = m_pTexture->getSubTexture(subTextureName);

    GLfloat vertexData[] =
    {
        //vertices      //texture
        //X   Y         //U                         V
        0.f,  0.f,      subTexture.leftBottomUV.x,  subTexture.leftBottomUV.y,
        1.f,  0.f,      subTexture.rightTopUV.x,    subTexture.leftBottomUV.y,
        1.f,  1.f,      subTexture.rightTopUV.x,    subTexture.rightTopUV.y,

        1.f,  1.f,      subTexture.rightTopUV.x,    subTexture.rightTopUV.y,
        0.f,  1.f,      subTexture.leftBottomUV.x,  subTexture.rightTopUV.y,
        0.f,  0.f,      subTexture.leftBottomUV.x,  subTexture.leftBottomUV.y,
    };


    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);


    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4*sizeof(GL_FLOAT), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4*sizeof(GL_FLOAT), (void*)(2*sizeof(GL_FLOAT)));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


Sprite::~Sprite()
{
    glDeleteBuffers(1, &m_VBO);
    glDeleteVertexArrays(1, &m_VAO);
}

void Sprite::render() const
{
    m_pShaderProg->use();
    glm::mat4 modelMatrix = glm::mat4(1.f);

    modelMatrix = glm::translate(modelMatrix, glm::vec3(m_position, 0.f));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0.5f * m_size.x, 0.5f * m_size.y, 0.f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(m_rotation), glm::vec3(0.f, 0.f, 1.f));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.5f * m_size.x, -0.5f * m_size.y, 0.f));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(m_size, 1.f));

    glBindVertexArray(m_VAO);
    glActiveTexture(GL_TEXTURE0);


    m_pTexture->bind();
    m_pShaderProg->setUniform("modelMatrix", modelMatrix);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    m_pShaderProg->unUse();
    m_pTexture->unbind();
    glBindVertexArray(0);

}



}
