#include "PhysicsEngine.h"

#include "../Game/GameObjects/IGameObject.h"
#include "../Game/Level.h"

#include <cmath>
#include <iostream>
namespace Physics
{
    std::list<std::shared_ptr<IDynamicGameObject>> PhysicsEngine::m_dynamicObjects;
    std::shared_ptr<Level>   PhysicsEngine::m_currentLevel;

    void PhysicsEngine::init()
    {

    }

    void PhysicsEngine::terminate()
    {
        m_dynamicObjects.clear();
        m_currentLevel.reset();
    }

    void PhysicsEngine::addDynamicObject(std::shared_ptr<IDynamicGameObject> object)
    {
        m_dynamicObjects.push_back(std::move(object));
    }

    void PhysicsEngine::setLevel(std::shared_ptr<Level> level)
    {
        m_currentLevel = std::move(level);
    }

    void PhysicsEngine::update(double delta)
    {
        //delta in milli
        float dt = delta / 1000.f;
        for (std::list<std::shared_ptr<IDynamicGameObject>>::iterator object = m_dynamicObjects.begin();
             object != m_dynamicObjects.end(); )
        {
            if ((*object)->isMoving())
            {
                std::cout << "Velocity.x = " << (*object)->getVelocity().x << "\ty = " << (*object)->getVelocity().y << '\n';
                // coordinate alignment
                if ((*object)->getDirection().x != 0.f)
                {
                    (*object)->getPosition().y = static_cast<unsigned int>((*object)->getPosition().y / 4.f + 0.5f) * 4.f;
                }
                else if ((*object)->getDirection().y != 0.f)
                {
                    (*object)->getPosition().x = static_cast<unsigned int>((*object)->getPosition().x / 4.f + 0.5f) * 4.f;
                }

                glm::vec2 newPosition = (*object)->getPosition() + dt
                                        * (*object)->getVelocity() * (*object)->getDirection();
                std::vector<std::shared_ptr<IStaticGameObject>> staticObjects =
                    m_currentLevel->getObjectsInArea(newPosition,
                                                     newPosition + (*object)->getSize());
                bool collision = false;
                for(auto& staticObject : staticObjects)
                {
                    if (staticObject->checkCollision(*object, newPosition))
                        collision = true;
                }
                if (!collision)
                {
                    (*object)->getPosition() = newPosition;
                    (*object)->setCurrentSmooth((*object)->getNormalSmooth());
                    (*object)->setSpeed((*object)->getMaxSpeed());
                }
            }
            if (!(*object)->isAlive())
                object = m_dynamicObjects.erase(object);
            ++object;
        }
    }
}
