#pragma once

#include "IGameObject.h"

#include <memory>
#include <array>

namespace RenderEngine {
    class Sprite;
}

class Border : public IStaticGameObject
{
public:

    Border(const glm::vec2& position, const glm::vec2& size, float layer = 0.f);
    virtual ~Border();
    virtual void render() const override;

private:
    std::shared_ptr<RenderEngine::Sprite>   m_pSprite;
};
