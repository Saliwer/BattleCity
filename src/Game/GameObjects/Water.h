#pragma once

#include "IGameObject.h"

#include <memory>
#include <array>

namespace RenderEngine {
    class AnimatedSprite;
}

class Water : public IStaticGameObject
{
public:

    enum class EWaterLocation : uint8_t
    {
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight
    };

    Water(const glm::vec2& position, const glm::vec2& size, float layer = 0.f);
    virtual ~Water();
    virtual void render() const override;
    virtual void update(double delta) override;

private:
    void renderBrick(EWaterLocation eLocation) const;

private:
    std::shared_ptr<RenderEngine::AnimatedSprite>   m_pSprite;
    std::array<glm::vec2, 4>                        m_blockOffsets;
};
