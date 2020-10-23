// OpenGL
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// STL
#include <iostream>
#include <vector>
#include <string>
#include <chrono>

// My classes
#include "Renderer/ShaderProgram.h"
#include "Renderer/Texture2D.h"
#include "Renderer/Sprite.h"
#include "Renderer/AnimatedSprite.h"
#include "Manager/ResourceManager.h"

// Math
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void WindowResizeCallback(GLFWwindow* window, int width, int height);

int g_SCREEN_WIDTH = 640;
int g_SCREEN_HEIGHT = 480;

int main(int argc, char* argv[])
{
    /* Initialize the library */
    if (!glfwInit()){
        std::cout << "GLFW init failed!\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(g_SCREEN_WIDTH, g_SCREEN_HEIGHT, "Hello World", NULL, NULL);
    if (!window)
    {
        std::cout << "glfwCreateWindow failed!\n";
        glfwTerminate();
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, WindowResizeCallback);
    glfwSetKeyCallback(window, KeyCallback);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (!gladLoadGL())
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }




    ResourceManager::setExecutablePath(argv[0]);
    std::shared_ptr<Renderer::ShaderProgram> shaderProgram =
        ResourceManager::loadShaders("FirstProgram",
                               "resource/shaders/vertex.vs",
                               "resource/shaders/fragment.fs");

    std::shared_ptr<Renderer::Texture2D> myTexture =
        ResourceManager::loadTexture("FirstTexture",
                               "resource/textures/map_16x16.png");


    std::vector<std::string> subTextures = {"Brick", "BrickTop", "BrickBottom", "BrickLeft",
                                            "BrickRight", "BrickTopLeft", "BrickTopRight",
                                            "BrickBottomLeft", "BrickBottomRight", "Beton"};
    myTexture->genSubTextures(subTextures, glm::vec2(0.f, (float)myTexture->getHeight()), glm::vec2(16.f, 16.f));

    std::shared_ptr<Renderer::Sprite> brickSprite =
        ResourceManager::createSprite("BrickSprite", "FirstProgram", "FirstTexture", "Brick", 50, 50);
    brickSprite->setPosition(glm::vec2(300.f, 100.f));

    std::shared_ptr<Renderer::Sprite> betonSprite =
        ResourceManager::createSprite("BetonSprite", "FirstProgram", "FirstTexture", "Beton", 50, 50);
    betonSprite->setPosition(glm::vec2(250.f, 100.f));
    betonSprite->setSubTexture("BrickTopLeft");

    std::shared_ptr<Renderer::AnimatedSprite> pAnimeSprite =
        ResourceManager::createAnimatedSprite("AnimeSprite", "FirstProgram", "FirstTexture", 50, 50);
    pAnimeSprite->setPosition(glm::vec2(100.f, 100.f));
    for (auto& elem : subTextures)
        pAnimeSprite->addSubTexture(elem, 1e9);

    glm::mat4 projectionMatrix = glm::ortho(0.0f, (float)g_SCREEN_WIDTH,
                                            0.0f, (float)g_SCREEN_HEIGHT,
                                            100.0f, -100.0f);


    shaderProgram->use();
    shaderProgram->setUniform("projectionMatrix", projectionMatrix);
    shaderProgram->setUniform("myTexture", 0);



    auto lastTime = std::chrono::high_resolution_clock::now();
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        auto currentTime = std::chrono::high_resolution_clock::now();
        uint64_t duration = std::chrono::duration_cast<std::chrono::nanoseconds>
                                         (currentTime - lastTime).count();
        lastTime = currentTime;
        /* Render here */
        glClearColor(0.5f, 0.25f, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        pAnimeSprite->update(duration);
        pAnimeSprite->render();
        brickSprite->render();
        betonSprite->render();
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    ResourceManager::unloadResources();

    glfwTerminate();
    return 0;
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
}

void WindowResizeCallback(GLFWwindow* window, int width, int height)
{
    g_SCREEN_WIDTH = width;
    g_SCREEN_HEIGHT = height;
    glViewport(0, 0, g_SCREEN_WIDTH, g_SCREEN_HEIGHT);
}
