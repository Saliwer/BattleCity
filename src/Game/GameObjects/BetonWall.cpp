#include "BetonWall.h"

#include "../../Renderer/Sprite.h"
#include "../../Manager/ResourceManager.h"


BetonWall::BetonWall(EBetonWallState betonWallState,
                     const glm::vec2& position, const glm::vec2& size, float layer)
                     : m_eCurrentBetonState(betonWallState)
                     , IStaticGameObject(position, size, layer)
{
    m_pSprite = ResourceManager::getSprite("beton8x8");
}

BetonWall::~BetonWall()
{}

void BetonWall::render() const
{
    if (m_eCurrentBetonState != EBetonWallState::Destroyed)
        m_pSprite->render(m_position, m_size, m_layer);
}
