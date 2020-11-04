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
    std::shared_ptr<RenderEngine::ShaderProgram> tankShaderProgram =
        ResourceManager::getShaderProgram("spriteShader");

    if (!tankShaderProgram)
        return false;

    std::shared_ptr<RenderEngine::AnimatedSprite> pTankAnimeSprite =
        ResourceManager::getAnimatedSprite("tankYellowType1AnimSprite");

    if (!pTankAnimeSprite)
        return false;

    m_pTank = std::make_unique<Tank>(pTankAnimeSprite, glm::vec2(0.f, 0.f), glm::vec2(16.f, 16.f), glm::vec2(0.f, 1.f), 0.8f);
    m_pLevel = std::make_unique<Level>(ResourceManager::getLevels()[0]);

    glm::mat4 projectionMatrix = glm::ortho(0.0f, (float)m_windowSize.x,
                                            0.0f, (float)m_windowSize.y,
                                            100.0f, -100.0f);
    //projectionMatrix[0] = projectionMatrix[0] / (m_windowSize.x / (float)m_windowSize.y);

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
        m_pTank->setSpriteState("tankTopState");
        m_pTank->move(true);
    }
    else if (m_keys[GLFW_KEY_D]){
        m_pTank->setDirection(glm::vec2(1.f, 0.f));
        m_pTank->setSpriteState("tankRightState");
        m_pTank->move(true);
    }
    else if (m_keys[GLFW_KEY_S]){
        m_pTank->setDirection(glm::vec2(0.f, -1.f));
        m_pTank->setSpriteState("tankBottomState");
        m_pTank->move(true);
    }
    else if(m_keys[GLFW_KEY_A]){
        m_pTank->setDirection(glm::vec2(-1.f, 0.f));
        m_pTank->setSpriteState("tankLeftState");
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
