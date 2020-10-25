#include "Game.h"

#include <vector>
#include <memory>

#include "../Manager/ResourceManager.h"
#include "../Renderer/ShaderProgram.h"
#include "../Renderer/Texture2D.h"
#include "../Renderer/Sprite.h"
#include "../Renderer/AnimatedSprite.h"
#include "Tank.h"

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
    std::shared_ptr<RenderEngine::ShaderProgram> tankShaderProgram =
        ResourceManager::loadShaders("TankShaderProgram",
                                     "resource/shaders/vertex.vs",
                                     "resource/shaders/fragment.fs");
    if (!tankShaderProgram)
        return false;

    std::shared_ptr<RenderEngine::Texture2D> tanksTexture =
        ResourceManager::loadTexture("TanksTexture",
                                     "resource/textures/tanks.png");
    if (!tanksTexture)
        return false;


    std::vector<std::string> subTextures = {
        "TankUp1",
        "TankUp2",
        "TankLeft1",
        "TankLeft2",
        "TankDown1",
        "TankDown2",
        "TankRight1",
        "TankRight2"
    };

    tanksTexture->genSubTextures(subTextures,
                                 glm::vec2(0.f, (float)tanksTexture->getHeight()),
                                 glm::vec2(16.f, 16.f));

    std::shared_ptr<RenderEngine::AnimatedSprite> pTankAnimeSprite =
        ResourceManager::createAnimatedSprite("TankAnimeSprite", "TankShaderProgram", "TanksTexture", 50, 50);

    if (!pTankAnimeSprite)
        return false;

    std::list<std::pair<std::string, uint64_t>> tankStatesUp;
    std::list<std::pair<std::string, uint64_t>> tankStatesLeft;
    std::list<std::pair<std::string, uint64_t>> tankStatesRight;
    std::list<std::pair<std::string, uint64_t>> tankStatesDown;
    tankStatesUp.emplace_back("TankUp1", 1.5e5);
    tankStatesUp.emplace_back("TankUp2", 1.5e5);
    tankStatesLeft.emplace_back("TankLeft1", 1.5e5);
    tankStatesLeft.emplace_back("TankLeft2", 1.5e5);
    tankStatesDown.emplace_back("TankDown1", 1.5e5);
    tankStatesDown.emplace_back("TankDown2", 1.5e5);
    tankStatesRight.emplace_back("TankRight1", 1.5e5);
    tankStatesRight.emplace_back("TankRight2", 1.5e5);

    pTankAnimeSprite->insertState("tankStatesUp", std::move(tankStatesUp));
    pTankAnimeSprite->insertState("tankStatesLeft", std::move(tankStatesLeft));
    pTankAnimeSprite->insertState("tankStatesRight", std::move(tankStatesRight));
    pTankAnimeSprite->insertState("tankStatesDown", std::move(tankStatesDown));

    pTankAnimeSprite->setState("tankStatesUp");


    m_pTank = std::make_unique<Tank>(pTankAnimeSprite, glm::vec2(300.f, 250.f), 2.f);


    glm::mat4 projectionMatrix = glm::ortho(0.0f, (float)m_windowSize.x,
                                            0.0f, (float)m_windowSize.y,
                                            100.0f, -100.0f);


    tankShaderProgram->use();
    tankShaderProgram->setUniform("projectionMatrix", projectionMatrix);
    tankShaderProgram->setUniform("myTexture", 0);
    tankShaderProgram->unUse();

    return true;
}

void Game::terminate()
{
    Tank* p = m_pTank.release();
    delete p;
}

void Game::render()
{
    if (m_pTank)
        m_pTank->render();
}

void Game::update(uint64_t deltaTime)
{
    if (m_pTank)
        m_pTank->update(deltaTime);
}

void Game::processInput(uint64_t deltaTime)
{
    if (m_keys[GLFW_KEY_W]){
        m_pTank->setDirection(glm::vec2(0.f, 1.f));
        m_pTank->setSpriteState("tankStatesUp");
        m_pTank->move(true);
    }
    else if (m_keys[GLFW_KEY_D]){
        m_pTank->setDirection(glm::vec2(1.f, 0.f));
        m_pTank->setSpriteState("tankStatesRight");
        m_pTank->move(true);
    }
    else if (m_keys[GLFW_KEY_S]){
        m_pTank->setDirection(glm::vec2(0.f, -1.f));
        m_pTank->setSpriteState("tankStatesDown");
        m_pTank->move(true);
    }
    else if(m_keys[GLFW_KEY_A]){
        m_pTank->setDirection(glm::vec2(-1.f, 0.f));
        m_pTank->setSpriteState("tankStatesLeft");
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
