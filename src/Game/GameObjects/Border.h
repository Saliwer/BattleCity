#pragma once

#include "IGameObject.h"

#include <memory>
#include <array>

namespace RenderEngine {
    class Sprite;
}

class Border : public IGameObject
{
public:

    Border(const glm::vec2& position, const glm::vec2& size,
           const glm::vec2& direction = glm::vec2(1.f, 0.f), float layer = 0.f);
    virtual ~Border();
    virtual void render() const override;
    virtual void update(uint64_t delta) override {}

private:
    std::shared_ptr<RenderEngine::Sprite>   m_pSprite;
};
