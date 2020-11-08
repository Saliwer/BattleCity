#pragma once
#include "Sprite.h"
#include <list>
#include <map>
#include <utility>

namespace RenderEngine
{

class AnimatedSprite : public Sprite
{
public:

    struct Frame
    {
        Frame(std::string name, uint64_t duration)
        : m_subTextureName(std::move(name))
        , m_currentFrameDuration(duration)
        {}
        ~Frame() = default;

        std::string m_subTextureName;
        uint64_t    m_currentFrameDuration;
    };

    AnimatedSprite(std::shared_ptr<ShaderProgram> pShaderProg,
                   std::shared_ptr<Texture2D> pTexture,
                   std::string subTextureName,
                   std::vector<Frame> = {});

    virtual ~AnimatedSprite();

    void update(uint64_t delta);
    void addFrame(std::string name, uint64_t duration);
    virtual void render(const glm::vec2& position, const glm::vec2& size, const glm::vec2& direction) const override;

protected:
    std::vector<Frame>  m_frames;
    size_t              m_activeFrame;
    uint64_t            m_currentAnimationTime;
};

}
