#pragma once

#include "IGameObject.h"

#include <memory>
#include <array>

namespace RenderEngine {
    class Sprite;
}

class BrickWall : public IStaticGameObject
{
public:

    enum class EBrickWallState : uint8_t
    {
        fullBrick,
        topBrick,
        bottomBrick,
        destroyed
    };

    BrickWall(EBrickWallState brickWallState,
              const glm::vec2& position, const glm::vec2& size, float layer = 0.f);
    virtual ~BrickWall();
    virtual void render() const override;

private:
    EBrickWallState                                         m_eCurrentBrickState;
    std::array<std::shared_ptr<RenderEngine::Sprite>, 3>    m_pSprites;
};
