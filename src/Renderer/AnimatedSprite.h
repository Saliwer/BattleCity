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
        Frame(std::string name, double duration)
        : m_subTextureName(std::move(name))
        , m_currentFrameDuration(duration)
        {}
        ~Frame() = default;

        std::string m_subTextureName;
        double    m_currentFrameDuration;
    };

    AnimatedSprite(std::shared_ptr<ShaderProgram> pShaderProg,
                   std::shared_ptr<Texture2D> pTexture,
                   std::string subTextureName,
                   std::vector<Frame> = {});

    virtual ~AnimatedSprite();

    void update(double delta);
    void addFrame(std::string name, double duration);
    virtual void render(const glm::vec2& position, const glm::vec2& size, const glm::vec2& direction, float layer = 0.f) const override;
    virtual void render(const glm::vec2& position, const glm::vec2& size, float layer = 0.f) const override;

protected:
    std::vector<Frame>  m_frames;
    size_t              m_activeFrame;
    double              m_currentAnimationTime;
};

}
