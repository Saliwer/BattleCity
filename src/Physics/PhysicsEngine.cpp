#include "PhysicsEngine.h"

#include <glm/vec2.hpp>

namespace Physics
{
   std::unordered_set<std::shared_ptr<IDynamicGameObject>> PhysicsEngine::m_dynamicObjects;

    void PhysicsEngine::init()
    {

    }

    void PhysicsEngine::terminate()
    {
        m_dynamicObjects.clear();
    }

    void PhysicsEngine::addDynamicObject(std::shared_ptr<IDynamicGameObject> object)
    {
        m_dynamicObjects.insert(std::move(object));
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
                object->setPosition(newPosition);
            }
        }
    }
}
