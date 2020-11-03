#pragma once

#include "IGameObject.h"

#include <memory>

namespace RenderEngine {
    class Sprite;
}

class BrickWall : public IGameObject
{
    std::shared_ptr<RenderEngine::Sprite> m_pSprite;
 public:
    BrickWall(std::shared_ptr<RenderEngine::Sprite> pSprite,
              const glm::vec2& position, const glm::vec2& size,
              const glm::vec2& direction);
    virtual ~BrickWall();
    virtual void render() const override;
    virtual void update(uint64_t delta) override;

};
