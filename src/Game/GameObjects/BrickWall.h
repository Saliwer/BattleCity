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

    enum class EBrickWallType : uint8_t
    {
        All = 0,
        Top,
        Bottom,
        Left,
        Right,
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight
    };

    enum class EBrickWallState : uint8_t
    {
        fullBrick,
        topLeftBrick,
        topRightBrick,
        topBrick,
        bottomLeftBrick,
        leftBrick,

        topRightBottomLeftBrick,
        topBottomLeftBrick,
        bottomRightBrick,
        topLeftBottomRightBrick,
        rightBrick,
        topBottomRightBrick,

        bottomBrick,
        bottomTopLeftBrick,
        bottomTopRightBrick,
        destroyed
    };

    enum class EBrickLocation : uint8_t
    {
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight
    };

    BrickWall(EBrickWallType brickWallType,
              const glm::vec2& position, const glm::vec2& size, float layer = 0.f);
    virtual ~BrickWall();
    virtual void render() const override;

private:
    void renderBrick(EBrickLocation eLocation) const;

private:
    std::array<EBrickWallState, 4>                          m_eCurrentBrickStates;
    std::array<std::shared_ptr<RenderEngine::Sprite>, 15>   m_pSprites;
    std::array<glm::vec2, 4>                                m_blockOffsets;
};
