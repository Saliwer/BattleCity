#pragma once

#include "IGameObject.h"

#include <memory>
#include <array>

namespace RenderEngine {
    class Sprite;
}

class Ice : public IGameObject
{
public:

    enum class EIceLocation
    {
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight
    };

    Ice(const glm::vec2& position, const glm::vec2& size,
         const glm::vec2& direction);
    virtual ~Ice();
    virtual void render() const override;
    virtual void update(uint64_t delta) override {}

private:
    void renderBrick(EIceLocation eLocation) const;

private:
    std::shared_ptr<RenderEngine::Sprite>  m_pSprite;
    std::array<glm::vec2, 4>               m_blockOffsets;
};
