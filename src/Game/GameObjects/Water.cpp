#include "Water.h"

#include "../../Renderer/AnimatedSprite.h"
#include "../../Manager/ResourceManager.h"


Water::Water(const glm::vec2& position, const glm::vec2& size,
             const glm::vec2& direction, float layer) : IGameObject(position, size, direction, layer)
{
    m_blockOffsets = {
        glm::vec2(0.f, m_size.y / 2.f),
        glm::vec2(m_size.x / 2.f, m_size.y / 2.f),
        glm::vec2(0.f, 0.f),
        glm::vec2(m_size.x / 2.f, 0.f)
    };

    m_pSprite = ResourceManager::getAnimatedSprite("water");
}

Water::~Water()
{}

void Water::renderBrick(EWaterLocation eLocation) const
{
    m_pSprite->render(m_position + m_blockOffsets[static_cast<size_t>(eLocation)],
                      m_size / 2.f, m_direction, m_layer);

}

void Water::render() const
{
    renderBrick(EWaterLocation::TopLeft);
    renderBrick(EWaterLocation::TopRight);
    renderBrick(EWaterLocation::BottomLeft);
    renderBrick(EWaterLocation::BottomRight);
}

void Water::update(uint64_t delta)
{
    m_pSprite->update(delta);
}
