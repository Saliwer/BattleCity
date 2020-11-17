#include "PhysicsEngine.h"

#include "../Game/GameObjects/IGameObject.h"
#include "../Game/Level.h"

#include <cmath>
#include <iostream>
namespace Physics
{
    std::unordered_set<std::shared_ptr<IDynamicGameObject>> PhysicsEngine::m_dynamicObjects;
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
        m_dynamicObjects.insert(std::move(object));
    }

    void PhysicsEngine::setLevel(std::shared_ptr<Level> level)
    {
        m_currentLevel = std::move(level);
    }

    void PhysicsEngine::update(double delta)
    {
        for (auto& object : m_dynamicObjects)
        {
            if (object->isMoving())
            {
                //delta in milli!
                float dt = delta / 10.f;
                glm::vec2 newPosition = object->getPosition() + dt
                                        * object->getVelocity() * object->getDirection();
                std::vector<std::shared_ptr<IStaticGameObject>> m_staticObjects =
                    m_currentLevel->getObjectsInArea(newPosition,
                                                     newPosition + object->getSize());
                object->getPosition() = newPosition;
            }
            else if (object->getVelocity().x > 1e-10 || object->getVelocity().y > 1e-10)
            {
               //delta in milli!
                float dt = delta / 10.f;
                glm::vec2 newPosition = object->getPosition() + dt
                                        * object->getVelocity() * object->getDirection();
                object->getPosition() = newPosition;
            }
        }
    }
}
