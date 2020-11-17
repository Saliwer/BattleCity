#include "Water.h"

#include "../../Renderer/AnimatedSprite.h"
#include "../../Manager/ResourceManager.h"


Water::Water(const glm::vec2& position, const glm::vec2& size, float layer)
            : IStaticGameObject(position, size, layer)
{
    m_pSprite = ResourceManager::getAnimatedSprite("water");
}

Water::~Water()
{}

void Water::render() const
{
    m_pSprite->render(m_position, m_size, m_layer);
}

void Water::update(double delta)
{
    m_pSprite->update(delta);
}
