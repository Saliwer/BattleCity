#include "BrickWall.h"

#include "../../Renderer/Sprite.h"
#include "../../Manager/ResourceManager.h"


BrickWall::BrickWall(EBrickWallType brickWallType,
                     const glm::vec2& position, const glm::vec2& size,
                     const glm::vec2& direction, float layer) : IGameObject(position, size, direction, layer)
{
    m_blockOffsets = {
        glm::vec2(0.f, m_size.y / 2.f),
        glm::vec2(m_size.x / 2.f, m_size.y / 2.f),
        glm::vec2(0.f, 0.f),
        glm::vec2(m_size.x / 2.f, 0.f)
    };

    m_pSprites[static_cast<size_t>(EBrickWallState::fullBrick)]                 = ResourceManager::getSprite("fullBrick8x8");
    m_pSprites[static_cast<size_t>(EBrickWallState::topLeftBrick)]              = ResourceManager::getSprite("topLeftBrick8x8");
    m_pSprites[static_cast<size_t>(EBrickWallState::topRightBrick)]             = ResourceManager::getSprite("topRightBrick8x8");
    m_pSprites[static_cast<size_t>(EBrickWallState::topBrick)]                  = ResourceManager::getSprite("topBrick8x8");
    m_pSprites[static_cast<size_t>(EBrickWallState::bottomLeftBrick)]           = ResourceManager::getSprite("bottomLeftBrick8x8");
    m_pSprites[static_cast<size_t>(EBrickWallState::leftBrick)]                 = ResourceManager::getSprite("leftBrick8x8");
    m_pSprites[static_cast<size_t>(EBrickWallState::topRightBottomLeftBrick)]   = ResourceManager::getSprite("topRightBottomLeftBrick8x8");
    m_pSprites[static_cast<size_t>(EBrickWallState::topBottomLeftBrick)]        = ResourceManager::getSprite("topBottomLeftBrick8x8");
    m_pSprites[static_cast<size_t>(EBrickWallState::bottomRightBrick)]          = ResourceManager::getSprite("bottomRightBrick8x8");
    m_pSprites[static_cast<size_t>(EBrickWallState::topLeftBottomRightBrick)]   = ResourceManager::getSprite("topLeftBottomRightBrick8x8");
    m_pSprites[static_cast<size_t>(EBrickWallState::rightBrick)]                = ResourceManager::getSprite("rightBrick8x8");
    m_pSprites[static_cast<size_t>(EBrickWallState::topBottomRightBrick)]       = ResourceManager::getSprite("topBottomRightBrick8x8");
    m_pSprites[static_cast<size_t>(EBrickWallState::bottomBrick)]               = ResourceManager::getSprite("bottomBrick8x8");
    m_pSprites[static_cast<size_t>(EBrickWallState::bottomTopLeftBrick)]        = ResourceManager::getSprite("bottomTopLeftBrick8x8");
    m_pSprites[static_cast<size_t>(EBrickWallState::bottomTopRightBrick)]       = ResourceManager::getSprite("bottomTopRightBrick8x8");

    m_eCurrentBrickStates.fill(EBrickWallState::destroyed);
    switch(brickWallType)
    {
    case EBrickWallType::All:
        m_eCurrentBrickStates.fill(EBrickWallState::fullBrick);
        break;
    case EBrickWallType::Top:
        m_eCurrentBrickStates[static_cast<size_t>(EBrickLocation::TopLeft)] = EBrickWallState::fullBrick;
        m_eCurrentBrickStates[static_cast<size_t>(EBrickLocation::TopRight)] = EBrickWallState::fullBrick;
        break;
    case EBrickWallType::Bottom:
        m_eCurrentBrickStates[static_cast<size_t>(EBrickLocation::BottomLeft)] = EBrickWallState::fullBrick;
        m_eCurrentBrickStates[static_cast<size_t>(EBrickLocation::BottomRight)] = EBrickWallState::fullBrick;
        break;
    case EBrickWallType::Left:
        m_eCurrentBrickStates[static_cast<size_t>(EBrickLocation::TopLeft)] = EBrickWallState::fullBrick;
        m_eCurrentBrickStates[static_cast<size_t>(EBrickLocation::BottomLeft)] = EBrickWallState::fullBrick;
        break;
    case EBrickWallType::Right:
        m_eCurrentBrickStates[static_cast<size_t>(EBrickLocation::TopRight)] = EBrickWallState::fullBrick;
        m_eCurrentBrickStates[static_cast<size_t>(EBrickLocation::BottomRight)] = EBrickWallState::fullBrick;
        break;
    case EBrickWallType::TopLeft:
        m_eCurrentBrickStates[static_cast<size_t>(EBrickLocation::TopLeft)] = EBrickWallState::fullBrick;
        break;
    case EBrickWallType::TopRight:
        m_eCurrentBrickStates[static_cast<size_t>(EBrickLocation::TopRight)] = EBrickWallState::fullBrick;
        break;
    case EBrickWallType::BottomLeft:
        m_eCurrentBrickStates[static_cast<size_t>(EBrickLocation::BottomLeft)] = EBrickWallState::fullBrick;
        break;
    case EBrickWallType::BottomRight:
        m_eCurrentBrickStates[static_cast<size_t>(EBrickLocation::BottomRight)] = EBrickWallState::fullBrick;
        break;
    }
}

BrickWall::~BrickWall()
{}

void BrickWall::renderBrick(EBrickLocation eLocation) const
{
    EBrickWallState state = m_eCurrentBrickStates[static_cast<size_t>(eLocation)];
    if (state != EBrickWallState::destroyed)
    {
        m_pSprites[static_cast<size_t>(state)]->render(m_position + m_blockOffsets[static_cast<size_t>(eLocation)],
                                                       m_size / 2.f, m_direction, m_layer);
    }
}

void BrickWall::render() const
{
    renderBrick(EBrickLocation::TopLeft);
    renderBrick(EBrickLocation::TopRight);
    renderBrick(EBrickLocation::BottomLeft);
    renderBrick(EBrickLocation::BottomRight);
}

