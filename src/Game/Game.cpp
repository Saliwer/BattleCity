#include "Game.h"

#include <vector>
#include <memory>

#include "../Manager/ResourceManager.h"
#include "../Renderer/ShaderProgram.h"
#include "../Renderer/Texture2D.h"
#include "../Renderer/Sprite.h"
#include "../Renderer/AnimatedSprite.h"
#include "GameObjects/Tank.h"
#include "Level.h"

#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

Game::Game(const glm::ivec2& windowSize) : m_windowSize(windowSize),
                                           m_gameState(EGameState::ACTIVE)
{
    m_keys.fill(false);
}

Game::~Game()
{}

bool Game::init()
{
    ResourceManager::loadJSONResources("resource/resources.json");
    ResourceManager::loadJSONLevels("resource/levels.json");
    std::shared_ptr<RenderEngine::ShaderProgram> tankShaderProgram =
        ResourceManager::getShaderProgram("spriteShader");

    if (!tankShaderProgram)
        return false;

    m_pTank = std::make_unique<Tank>(glm::vec2(0.f, 0.f), glm::vec2(Level::m_BLOCK_SIZE, Level::m_BLOCK_SIZE), glm::vec2(0.f, 1.f), 0.8f);
    m_pLevel = std::make_unique<Level>(ResourceManager::loadLevel(1));
    m_windowSize.x = static_cast<float>(m_pLevel->getLevelWidth());
    m_windowSize.y = static_cast<float>(m_pLevel->getLevelHeight());
    glm::mat4 projectionMatrix = glm::ortho(0.0f, (float)m_windowSize.x,
                                            0.0f, (float)m_windowSize.y,
                                            100.0f, -100.0f);

    tankShaderProgram->use();
    tankShaderProgram->setUniform("projectionMatrix", projectionMatrix);
    tankShaderProgram->setUniform("myTexture", 0);
    tankShaderProgram->unUse();

    return true;
}

void Game::render()
{
    if (m_pTank)
        m_pTank->render();
    if (m_pLevel)
        m_pLevel->render();

}

void Game::update(uint64_t deltaTime)
{
    if (m_pTank)
        m_pTank->update(deltaTime);
    if (m_pLevel)
        m_pLevel->update(deltaTime);
}

void Game::processInput(uint64_t deltaTime)
{
    if (m_keys[GLFW_KEY_W]){
        m_pTank->setDirection(glm::vec2(0.f, 1.f));
        m_pTank->move(true);
    }
    else if (m_keys[GLFW_KEY_D]){
        m_pTank->setDirection(glm::vec2(1.f, 0.f));
        m_pTank->move(true);
    }
    else if (m_keys[GLFW_KEY_S]){
        m_pTank->setDirection(glm::vec2(0.f, -1.f));
        m_pTank->move(true);
    }
    else if(m_keys[GLFW_KEY_A]){
        m_pTank->setDirection(glm::vec2(-1.f, 0.f));
        m_pTank->move(true);
    }
    else
        m_pTank->move(false);
}

void Game::setKey(int key, int action)
{
    if (action == GLFW_PRESS)
        m_keys[key] = true;
    else if (action == GLFW_RELEASE)
        m_keys[key] = false;
}

size_t Game::getCurrentLevelWidth() const { return m_pLevel->getLevelWidth(); }
size_t Game::getCurrentLevelHeight() const { return m_pLevel->getLevelHeight(); }
