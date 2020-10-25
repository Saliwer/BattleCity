#pragma once


#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

#include <glad/glad.h>
#include <memory>
#include <glm/vec2.hpp>

namespace Renderer
{
    class Texture2D;
    class ShaderProgram;
    struct SubTexture;

    class Sprite
    {
    protected:
        std::shared_ptr<ShaderProgram>  m_pShaderProg;
        std::shared_ptr<Texture2D>      m_pTexture;
        std::string                     m_subTextureName;
        glm::vec2                       m_position;
        glm::vec2                       m_size;
        float                           m_rotation;
        VertexBuffer                    m_vertexCoords;
        VertexBuffer                    m_textureCoords;
        IndexBuffer                     m_indices;
        VertexArray                     m_vertexArray;

    public:
        Sprite(std::shared_ptr<ShaderProgram> pShaderProg,
               std::shared_ptr<Texture2D> pTexture,
               const std::string& subTextureName,
               const glm::vec2& position = glm::vec2(0.f),
               const glm::vec2& size = glm::vec2(1.f),
               float rotation = 0.f);
        virtual ~Sprite();

        Sprite() = delete;
        Sprite(const Sprite&) = delete;
        Sprite& operator=(const Sprite&) = delete;
        Sprite(Sprite&&) = delete;
        Sprite&& operator=(Sprite&&) = delete;


        virtual void render();

        void setSubTexture(const std::string& name);
        void setPosition(const glm::vec2& position){ m_position = position; }
        void setSize(const glm::vec2& size){ m_size = size; }
        void setRotation(float angle){ m_rotation = angle; }
        const glm::vec2& getPosition() const { return m_position; }
        const glm::vec2& getSize() const { return m_size; }
        float getRotation() const { return m_rotation; }
    protected:
        void changeTextureCoord(const SubTexture& newCoords);
    };
}
