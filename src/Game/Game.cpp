#include "Game.h"

#include <vector>
#include <memory>

#include "../Manager/ResourceManager.h"
#include "../Physics/PhysicsEngine.h"
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

Game::Game(const glm::ivec2& windowSize) : m_windowSize(windowSize)
                                         , m_gameState(EGameState::ACTIVE)
                                         , m_gameDifficulty(EGameDifficulty::EASY)
{
    m_keys.fill(false);
}

Game::~Game()
{}

bool Game::init()
{
    ResourceManager::loadJSONResources("resource/resources.json");
    ResourceManager::loadJSONLevels("resource/TiledLevels.json");
    std::shared_ptr<RenderEngine::ShaderProgram> tankShaderProgram =
        ResourceManager::getShaderProgram("spriteShader");

    if (!tankShaderProgram)
        return false;

    m_pLevel = createLevel(5);
    m_pTank = std::make_shared<Tank>(m_pLevel->getPlayer1RespawnSpot(),
                                     glm::vec2(Level::m_BLOCK_SIZE*2, Level::m_BLOCK_SIZE*2),
                                     glm::vec2(0.f, 1.f));

    Physics::PhysicsEngine::addDynamicObject(m_pTank);
    Physics::PhysicsEngine::setLevel(m_pLevel);

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

void Game::update(double deltaTime)
{
    if (m_pLevel)
        m_pLevel->update(deltaTime);
    if (m_pTank)
        m_pTank->update(deltaTime);

}

void Game::processInput(double deltaTime)
{
    if (m_pTank->isSpawning())
        return;
    if (m_keys[GLFW_KEY_W]){
        m_pTank->move(true);
        m_pTank->setDirection(glm::vec2(0.f, 1.f));
        m_pTank->setSprite(ResourceManager::getAnimatedSprite("tankYellowType1Top"));
        m_pTank->getVelocity().y = m_pTank->getCurrentSpeed();
    }
    else if (m_keys[GLFW_KEY_D]){
        m_pTank->move(true);
        m_pTank->setDirection(glm::vec2(1.f, 0.f));
        m_pTank->setSprite(ResourceManager::getAnimatedSprite("tankYellowType1Right"));
        m_pTank->getVelocity().x = m_pTank->getCurrentSpeed();
    }
    else if (m_keys[GLFW_KEY_S]){
        m_pTank->move(true);
        m_pTank->setDirection(glm::vec2(0.f, -1.f));
        m_pTank->setSprite(ResourceManager::getAnimatedSprite("tankYellowType1Bottom"));
        m_pTank->getVelocity().y = m_pTank->getCurrentSpeed();
    }
    else if(m_keys[GLFW_KEY_A]){
        m_pTank->move(true);
        m_pTank->setDirection(glm::vec2(-1.f, 0.f));
        m_pTank->setSprite(ResourceManager::getAnimatedSprite("tankYellowType1Left"));
        m_pTank->getVelocity().x = m_pTank->getCurrentSpeed();
    }
    else{
        m_pTank->move(false);
        m_pTank->getVelocity().x *= m_pTank->getCurrentSmooth();
        m_pTank->getVelocity().y *= m_pTank->getCurrentSmooth();
    }
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

std::shared_ptr<Level> Game::createLevel(size_t levelNumber)
{
    switch(m_gameDifficulty)
    {
    case EGameDifficulty::EASY:
        return std::make_shared<EasyLevel>(ResourceManager::loadLevel(levelNumber));
    case EGameDifficulty::MEDIUM:
        return nullptr;         // TODO!
    case EGameDifficulty::HARD:
        return nullptr;         // TODO!
    default:
        return nullptr;
    }
}
