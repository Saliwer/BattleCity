#pragma once

#include "IGameObject.h"

#include <memory>

namespace RenderEngine {
    class Sprite;
}

class Tree : public IStaticGameObject
{
public:

    Tree(const glm::vec2& position, const glm::vec2& size, float layer = 0.f);
    virtual ~Tree();
    virtual void render() const override;
    virtual bool checkCollision(std::shared_ptr<IDynamicGameObject> dynObject, const glm::vec2& newPos) override;

private:
    std::shared_ptr<RenderEngine::Sprite>  m_pSprite;
};
