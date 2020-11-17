#include "BrickWall.h"

#include "../../Renderer/Sprite.h"
#include "../../Manager/ResourceManager.h"


BrickWall::BrickWall(EBrickWallState brickWallState,
                     const glm::vec2& position, const glm::vec2& size, float layer)
                     : m_eCurrentBrickState(brickWallState)
                     , IStaticGameObject(position, size, layer)
{
    m_pSprites[static_cast<size_t>(EBrickWallState::fullBrick)]     = ResourceManager::getSprite("fullBrick8x8");
    m_pSprites[static_cast<size_t>(EBrickWallState::topBrick)]      = ResourceManager::getSprite("topBrick8x8");
    m_pSprites[static_cast<size_t>(EBrickWallState::bottomBrick)]   = ResourceManager::getSprite("bottomBrick8x8");
}

BrickWall::~BrickWall()
{}

void BrickWall::render() const
{
    if (m_eCurrentBrickState == EBrickWallState::destroyed)
        return;
    m_pSprites[static_cast<size_t>(m_eCurrentBrickState)]->render(m_position, m_size, m_layer);
}

