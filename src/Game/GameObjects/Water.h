#pragma once

#include "IGameObject.h"

#include <memory>

namespace RenderEngine {
    class AnimatedSprite;
}

class Water : public IStaticGameObject
{
public:

    Water(const glm::vec2& position, const glm::vec2& size, float layer = 0.f);
    virtual ~Water();
    virtual void render() const override;
    virtual void update(double delta) override;

private:
    std::shared_ptr<RenderEngine::AnimatedSprite>   m_pSprite;
};
