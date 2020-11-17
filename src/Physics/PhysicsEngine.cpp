#include "PhysicsEngine.h"

#include "../Game/GameObjects/IGameObject.h"
#include "../Game/Level.h"

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
            if (object->getVelocity() > 0)
            {
                //delta in microseconds!
                float dt = delta / 10000.f;
                glm::vec2 newPosition = object->getPosition() + dt
                                        * object->getVelocity() * object->getDirection();
                //m_currentLevel->getObjectsInArea(object->getPosition(), object->getPosition() + object->getSize());
                object->getPosition() = newPosition;
            }
        }
    }
}
