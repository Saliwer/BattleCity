#pragma once

#include <unordered_set>
#include <memory>
#include <glm/vec2.hpp>

class IDynamicGameObject;
class Level;

namespace Physics
{
    struct AABB{
        AABB(const glm::vec2& _leftBottomXY = glm::vec2(0.), const glm::vec2& _rightTopXY = glm::vec2(0.))
            : leftBottomXY(_leftBottomXY)
            , rightTopXY(_rightTopXY)
        {}

        glm::vec2 leftBottomXY;
        glm::vec2 rightTopXY;
    };

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
        static void setLevel(std::shared_ptr<Level> level);
        static void update(double delta);
    private:
        static std::unordered_set<std::shared_ptr<IDynamicGameObject>> m_dynamicObjects;
        static std::shared_ptr<Level>   m_currentLevel;
    };
}
