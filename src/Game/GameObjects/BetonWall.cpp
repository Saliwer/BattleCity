#include "BetonWall.h"

#include "../../Renderer/Sprite.h"
#include "../../Manager/ResourceManager.h"


BetonWall::BetonWall(EBetonWallType betonWallType,
                     const glm::vec2& position, const glm::vec2& size,
                     const glm::vec2& direction) : IGameObject(position, size, direction)
{
    m_blockOffsets = {
        glm::vec2(0.f, m_size.y / 2.f),
        glm::vec2(m_size.x / 2.f, m_size.y / 2.f),
        glm::vec2(0.f, 0.f),
        glm::vec2(m_size.x / 2.f, 0.f)
    };

    m_pSprite = ResourceManager::getSprite("beton8x8");

    m_eCurrentBetonStates.fill(EBetonWallState::Destroyed);
    switch(betonWallType)
    {
    case EBetonWallType::All:
        m_eCurrentBetonStates.fill(EBetonWallState::Unbroken);
        break;
    case EBetonWallType::Top:
        m_eCurrentBetonStates[static_cast<size_t>(EBetonLocation::TopLeft)] = EBetonWallState::Unbroken;
        m_eCurrentBetonStates[static_cast<size_t>(EBetonLocation::TopRight)] = EBetonWallState::Unbroken;
        break;
    case EBetonWallType::Bottom:
        m_eCurrentBetonStates[static_cast<size_t>(EBetonLocation::BottomLeft)] = EBetonWallState::Unbroken;
        m_eCurrentBetonStates[static_cast<size_t>(EBetonLocation::BottomRight)] = EBetonWallState::Unbroken;
        break;
    case EBetonWallType::Left:
        m_eCurrentBetonStates[static_cast<size_t>(EBetonLocation::TopLeft)] = EBetonWallState::Unbroken;
        m_eCurrentBetonStates[static_cast<size_t>(EBetonLocation::BottomLeft)] = EBetonWallState::Unbroken;
        break;
    case EBetonWallType::Right:
        m_eCurrentBetonStates[static_cast<size_t>(EBetonLocation::TopRight)] = EBetonWallState::Unbroken;
        m_eCurrentBetonStates[static_cast<size_t>(EBetonLocation::BottomRight)] = EBetonWallState::Unbroken;
        break;
    case EBetonWallType::TopLeft:
        m_eCurrentBetonStates[static_cast<size_t>(EBetonLocation::TopLeft)] = EBetonWallState::Unbroken;
        break;
    case EBetonWallType::TopRight:
        m_eCurrentBetonStates[static_cast<size_t>(EBetonLocation::TopRight)] = EBetonWallState::Unbroken;
        break;
    case EBetonWallType::BottomLeft:
        m_eCurrentBetonStates[static_cast<size_t>(EBetonLocation::BottomLeft)] = EBetonWallState::Unbroken;
        break;
    case EBetonWallType::BottomRight:
        m_eCurrentBetonStates[static_cast<size_t>(EBetonLocation::BottomRight)] = EBetonWallState::Unbroken;
        break;
    }
}

BetonWall::~BetonWall()
{}

void BetonWall::renderBrick(EBetonLocation eLocation) const
{
    EBetonWallState state = m_eCurrentBetonStates[static_cast<size_t>(eLocation)];
    if (state != EBetonWallState::Destroyed)
    {
        m_pSprite->render(m_position + m_blockOffsets[static_cast<size_t>(eLocation)], m_size / 2.f, m_direction);
    }
}

void BetonWall::render() const
{
    renderBrick(EBetonLocation::TopLeft);
    renderBrick(EBetonLocation::TopRight);
    renderBrick(EBetonLocation::BottomLeft);
    renderBrick(EBetonLocation::BottomRight);
}
