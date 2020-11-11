#pragma once

#include "IGameObject.h"

#include <memory>
#include <array>

namespace RenderEngine {
    class Sprite;
}

class BetonWall : public IGameObject
{
public:

    enum class EBetonWallType : uint8_t
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

    enum class EBetonWallState : uint8_t
    {
        Unbroken,
        Destroyed
    };

    enum class EBetonLocation : uint8_t
    {
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight
    };

    BetonWall(EBetonWallType betonWallType,
              const glm::vec2& position, const glm::vec2& size,
              const glm::vec2& direction, float layer = 0);
    virtual ~BetonWall();
    virtual void render() const override;
    virtual void update(uint64_t delta) override {}

private:
    void renderBrick(EBetonLocation eLocation) const;

private:
    std::array<EBetonWallState, 4>         m_eCurrentBetonStates;
    std::shared_ptr<RenderEngine::Sprite>  m_pSprite;
    std::array<glm::vec2, 4>               m_blockOffsets;
};
