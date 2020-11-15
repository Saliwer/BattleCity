#pragma once

#include <unordered_set>
#include <memory>

#include "../Game/GameObjects/IGameObject.h"

namespace Physics
{
    class PhysicsEngine
    {
    public:
        PhysicsEngine() = delete;
        PhysicsEngine(const PhysicsEngine&) = delete;
        PhysicsEngine& operator=(const PhysicsEngine&) = delete;
        PhysicsEngine(PhysicsEngine&&) = delete;
        PhysicsEngine& operator=(PhysicsEngine&&) = delete;
        ~PhysicsEngine() = delete;

        static void init();
        static void terminate();
        static void addDynamicObject(std::shared_ptr<IDynamicGameObject> object);
        static void update(double delta);
    private:
        static std::unordered_set<std::shared_ptr<IDynamicGameObject>> m_dynamicObjects;
    };
}
