#include "Border.h"

#include "../../Renderer/Sprite.h"
#include "../../Manager/ResourceManager.h"

Border::Border(const glm::vec2& position, const glm::vec2& size,
           const glm::vec2& direction, float layer)
           : IGameObject(position, size, direction, layer)
           , m_pSprite(ResourceManager::getSprite("border"))
{}

Border::~Border()
{}

void Border::render() const
{
    m_pSprite->render(m_position, m_size, m_direction, m_layer);
}
