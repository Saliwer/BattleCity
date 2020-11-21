#pragma once

#include "IGameObject.h"

#include <memory>
#include <glm/vec2.hpp>

namespace RenderEngine {
    class Sprite;
}

class Border : public IStaticGameObject
{
public:

    Border(const glm::vec2& position, const glm::vec2& size, float layer = 0.f);
    virtual ~Border();
    virtual void render() const override;
    virtual bool checkCollision(std::shared_ptr<IDynamicGameObject> dynObject, const glm::vec2& newPos) override;

protected:
    virtual void handlingCollision(Tank* tank) override {}
    virtual void handlingCollision(Bullet* bullet) override;

private:
    std::shared_ptr<RenderEngine::Sprite>   m_pSprite;
};
