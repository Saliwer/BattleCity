#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <array>
#include "glm/vec2.hpp"

class Game
{
    enum class EGameState{
        ACTIVE,
        PAUSE
    } ;

    glm::ivec2              m_windowSize;
    std::array<bool, 350>   m_keys;
    EGameState              m_gameState;

public:
    Game(const glm::ivec2& windowSize);
    ~Game();

    bool init();
    void render();
    void update(uint64_t deltaTime);
    void setKey(int key, int action);

};
