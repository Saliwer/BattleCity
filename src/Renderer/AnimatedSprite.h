#pragma once
#include "Sprite.h"
#include <list>
#include <utility>

namespace Renderer
{

class AnimatedSprite : public Sprite
{
    std::list<std::pair<std::string, uint64_t>> m_subTextures;
    uint64_t                        m_currentSpriteDuration;
    std::list<std::pair<std::string, uint64_t>>::const_iterator m_activeSprite;
public:
    AnimatedSprite(std::shared_ptr<ShaderProgram> pShaderProg,
                   std::shared_ptr<Texture2D> pTexture,
                   const glm::vec2& position = glm::vec2(0.f),
                   const glm::vec2& size = glm::vec2(1.f),
                   float rotation = 0.f);

    virtual ~AnimatedSprite();

    void addSubTexture(const std::string& name, uint64_t duration);

    void update(uint64_t delta);
    virtual void render() override;

};

}
