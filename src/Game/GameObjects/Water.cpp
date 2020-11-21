#include "Water.h"
#include "Tank.h"
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

bool Water::checkCollision(std::shared_ptr<IDynamicGameObject> dynObject, const glm::vec2& newPos)
{
    if (!hasIntersection(dynObject->getGlobalAABB()))
        return false;

    switch(dynObject->getType())
    {
        case IDynamicGameObject::EDynamicType::TankType1:
            handlingCollision(static_cast<Tank*>(dynObject.get()));
            break;
        case IDynamicGameObject::EDynamicType::Bullet:
            return false;
        default:
            //std::cerr << "Water: collision with unknown dynamic object\n";
            return false;
    }
    return true;
}

void Water::handlingCollision(Tank* tank)
{
    if (tank->getDirection().x > 0.f)
        tank->getPosition().x = m_position.x - tank->getSize().x;
    else if (tank->getDirection().x < 0.f)
        tank->getPosition().x = m_position.x + m_size.x;
    else if (tank->getDirection().y > 0.f)
        tank->getPosition().y = m_position.y - tank->getSize().y;
    else if (tank->getDirection().y < 0.f)
        tank->getPosition().y = m_position.y + m_size.y;
}

