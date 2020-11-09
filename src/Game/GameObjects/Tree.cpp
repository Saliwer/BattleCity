#include "Tree.h"

#include "../../Renderer/Sprite.h"
#include "../../Manager/ResourceManager.h"


Tree::Tree(const glm::vec2& position, const glm::vec2& size,
           const glm::vec2& direction) : IGameObject(position, size, direction)
{
    m_blockOffsets = {
        glm::vec2(0.f, m_size.y / 2.f),
        glm::vec2(m_size.x / 2.f, m_size.y / 2.f),
        glm::vec2(0.f, 0.f),
        glm::vec2(m_size.x / 2.f, 0.f)
    };

    m_pSprite = ResourceManager::getSprite("tree8x8");
}

Tree::~Tree()
{}

void Tree::renderBrick(ETreeLocation eLocation) const
{
    m_pSprite->render(m_position + m_blockOffsets[static_cast<size_t>(eLocation)], m_size / 2.f, m_direction);
}

void Tree::render() const
{
    renderBrick(ETreeLocation::TopLeft);
    renderBrick(ETreeLocation::TopRight);
    renderBrick(ETreeLocation::BottomLeft);
    renderBrick(ETreeLocation::BottomRight);
}
