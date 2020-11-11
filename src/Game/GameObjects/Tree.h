#pragma once

#include "IGameObject.h"

#include <memory>
#include <array>

namespace RenderEngine {
    class Sprite;
}

class Tree : public IGameObject
{
public:

    enum class ETreeLocation : uint8_t
    {
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight
    };

    Tree(const glm::vec2& position, const glm::vec2& size,
         const glm::vec2& direction, float layer = 0.f);
    virtual ~Tree();
    virtual void render() const override;
    virtual void update(uint64_t delta) override {}

private:
    void renderBrick(ETreeLocation eLocation) const;

private:
    std::shared_ptr<RenderEngine::Sprite>  m_pSprite;
    std::array<glm::vec2, 4>               m_blockOffsets;
};
