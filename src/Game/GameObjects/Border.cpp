#include "Border.h"
#include "Tank.h"
#include "Bullet.h"
#include "../../Renderer/Sprite.h"
#include "../../Manager/ResourceManager.h"


Border::Border(const glm::vec2& position, const glm::vec2& size, float layer)
           : IStaticGameObject(position, size, layer)
           , m_pSprite(ResourceManager::getSprite("border"))
{}

Border::~Border()
{}

void Border::render() const
{
    m_pSprite->render(m_position, m_size, m_layer);
}

bool Border::checkCollision(std::shared_ptr<IDynamicGameObject> dynObject, const glm::vec2& newPos)
{
    switch(dynObject->getType())
    {
        case IDynamicGameObject::EDynamicType::TankType1:
        {
            if (newPos.x > 208.f)
            {
                dynObject->getPosition().x = 208.f;
                return true;
            }
            if (newPos.x < 16.f)
            {
                dynObject->getPosition().x = 16.f;
                return true;
            }
            if (newPos.y > 240.f)
            {
                dynObject->getPosition().y = 240.f;
                return true;
            }
            if(newPos.y < 8.f)
            {
                dynObject->getPosition().y = 8.f;
                return true;
            }
            return false;
        }

        case IDynamicGameObject::EDynamicType::Bullet:
        {
            if (hasIntersection(dynObject->getGlobalAABB()))
            {
                handlingCollision(static_cast<Bullet*>(dynObject.get()));
                return true;
            }
            else
                return false;
        }

        default:
            //std::cerr << "Border: collision with unknown dynamic object\n";
            return false;
    }
    return false;
}

void Border::handlingCollision(Tank* tank)
{}

void Border::handlingCollision(Bullet* bullet)
{
    if (bullet->decLives() <= 0)
        bullet->setLive(false);
}
