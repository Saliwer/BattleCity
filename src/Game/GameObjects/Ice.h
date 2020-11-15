#pragma once

#include "IGameObject.h"

#include <memory>
#include <array>

namespace RenderEngine {
    class Sprite;
}

class Ice : public IStaticGameObject
{
public:

    enum class EIceLocation : uint8_t
    {
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight
    };

    Ice(const glm::vec2& position, const glm::vec2& size, float layer = 0.f);
    virtual ~Ice();
    virtual void render() const override;

private:
    void renderBrick(EIceLocation eLocation) const;

private:
    std::shared_ptr<RenderEngine::Sprite>  m_pSprite;
    std::array<glm::vec2, 4>               m_blockOffsets;
};
