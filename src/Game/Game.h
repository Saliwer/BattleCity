#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <array>
#include <memory>
#include "glm/vec2.hpp"

class Tank;
class Level;

class Game
{
public:
    enum class EGameState : uint8_t
    {
        ACTIVE,
        PAUSE
    };

    enum class EGameDifficulty : uint8_t
    {
        EASY,
        MEDIUM,
        HARD
    };

    Game(const glm::ivec2& windowSize);
    ~Game();

    bool init();
    void render();
    void update(uint64_t deltaTime);
    void processInput(uint64_t deltaTime);
    void setKey(int key, int action);

    size_t getCurrentLevelWidth() const;
    size_t getCurrentLevelHeight() const;

protected:
    std::unique_ptr<Level> createLevel(size_t levelNumber);

private:
    glm::ivec2              m_windowSize;
    std::array<bool, 350>   m_keys;
    EGameState              m_gameState;
    EGameDifficulty         m_gameDifficulty;
    std::unique_ptr<Level>  m_pLevel;
    std::unique_ptr<Tank>   m_pTank;
};
