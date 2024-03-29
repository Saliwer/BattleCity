#pragma once


#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

#include <glad/glad.h>
#include <memory>
#include <glm/vec2.hpp>
#include <vector>

namespace RenderEngine
{
    class Texture2D;
    class ShaderProgram;
    struct SubTexture;

    class Sprite
    {
    public:
        Sprite(std::shared_ptr<ShaderProgram> pShaderProg,
               std::shared_ptr<Texture2D> pTexture,
               std::string subTextureName);
        virtual ~Sprite();

        Sprite() = delete;
        Sprite(const Sprite&) = delete;
        Sprite& operator=(const Sprite&) = delete;
        Sprite(Sprite&&) = delete;
        Sprite&& operator=(Sprite&&) = delete;


        virtual void render(const glm::vec2& position, const glm::vec2& size, const glm::vec2& direction, float layer = 0) const;
        virtual void render(const glm::vec2& position, const glm::vec2& size, float layer = 0.f) const;
        virtual void update(double delta){}
        void setSubTexture(const std::string& name);

    protected:
        void changeTextureCoord(const SubTexture& newCoords);

        std::shared_ptr<ShaderProgram>  m_pShaderProg;
        std::shared_ptr<Texture2D>      m_pTexture;
        std::string                     m_activeSubTexture;
        VertexBuffer                    m_vertexCoords;
        VertexBuffer                    m_textureCoords;
        IndexBuffer                     m_indices;
        VertexArray                     m_vertexArray;
    };
}
