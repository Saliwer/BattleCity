#include "BrickWall.h"

#include "../../Renderer/Sprite.h"

BrickWall::BrickWall(std::shared_ptr<RenderEngine::Sprite> pSprite,
          const glm::vec2& position, const glm::vec2& size,
          const glm::vec2& direction) : IGameObject(position, size, direction),
                                        m_pSprite(pSprite)
{}

BrickWall::~BrickWall()
{}

void BrickWall::render() const
{
    if (m_pSprite)
        m_pSprite->render(m_position, m_size, m_direction);
}

void BrickWall::update(uint64_t delta)
{

}
