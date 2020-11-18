// OpenGL
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// STL
#include <iostream>
#include <chrono>
#include <memory>
#include <thread>

#include <cstdlib>
#include <ctime>

// My classes
#include "Game/Game.h"
#include "Manager/ResourceManager.h"
#include "Renderer/Renderer.h"
#include "Physics/PhysicsEngine.h"

// Math
#include <glm/vec2.hpp>

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void WindowResizeCallback(GLFWwindow* window, int width, int height);

glm::ivec2 g_WindowSize = glm::ivec2(32*8, 33*8);
std::unique_ptr<Game> g_Game = std::make_unique<Game>(g_WindowSize);

int main(int argc, char* argv[])
{
    // Initialize the library
    if (!glfwInit()){
        std::cerr << "GLFW init failed!\n";
        return -1;
    }

    // Set OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(g_WindowSize.x, g_WindowSize.y, "Battle City", NULL, NULL);
    if (!window)
    {
        std::cerr << "glfwCreateWindow failed!\n";
        glfwTerminate();
        return -1;
    }

    // Set callback functions
    glfwSetFramebufferSizeCallback(window, WindowResizeCallback);
    glfwSetKeyCallback(window, KeyCallback);

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Load GLAD functions
    if (!gladLoadGL())
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //Time init
    srand(time(NULL));


    // ResourceManager init
    ResourceManager::setExecutablePath(argv[0]);

    // Game init
    if (!g_Game->init())
    {
        std::cerr << "Couldn't init game!\n";
        return -1;
    }

    //Physics engine init
    Physics::PhysicsEngine::init();


    glfwSetWindowSize(window, 2*(int)g_Game->getCurrentLevelWidth(), 2*(int)g_Game->getCurrentLevelHeight());

    RenderEngine::Renderer::setClearColor(0.f, 0.f, 0.f, 1.f);
    RenderEngine::Renderer::setDepthTest(true);
    auto lastTime = std::chrono::high_resolution_clock::now();
    // game loop
    //----------
    const double MAXFPS = (1.0 / 60) * 1e3;
    while (!glfwWindowShouldClose(window))
    {
        // calculate delta time
        //---------------------
        auto currentTime = std::chrono::high_resolution_clock::now();
        double duration = std::chrono::duration<double, std::milli>(currentTime - lastTime).count();
        lastTime = currentTime;
        //std::cout << duration / 1e3 << '\n';
        std::cout << "FPS = " << 1 / (duration/1e3) << std::endl;
        std::this_thread::sleep_for(std::chrono::microseconds(static_cast<long>((MAXFPS - duration) * 1e3)));
        // poll for and process events
        //----------------------------
        glfwPollEvents();
        g_Game->processInput(duration);

        // update game state
        //------------------
        g_Game->update(duration);
        Physics::PhysicsEngine::update(duration);

        // render
        //-------
        RenderEngine::Renderer::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        g_Game->render();

        // Swap front and back buffers
        //----------------------------
        glfwSwapBuffers(window);

    }

    // clean-up before exit
    //---------------------
    Physics::PhysicsEngine::terminate();
    g_Game = nullptr;
    ResourceManager::unloadResources();
    glfwTerminate();
    return 0;
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
    g_Game->setKey(key, action);
}

void WindowResizeCallback(GLFWwindow* window, int width, int height)
{
    g_WindowSize.x = width;
    g_WindowSize.y = height;
    const float aspect_ratio = static_cast<float>(g_Game->getCurrentLevelWidth()) / g_Game->getCurrentLevelHeight();;
    unsigned int viewPortWidth = width;
    unsigned int viewPortHeight = height;
    unsigned int viewPortXOffset = 0;
    unsigned int viewPortYOffset = 0;

    if (((float)width / height) > aspect_ratio)
    {
        viewPortWidth = static_cast<unsigned int>(viewPortHeight * aspect_ratio);
        viewPortXOffset = (width - viewPortHeight) / 2;
    }
    else
    {
        viewPortHeight = static_cast<unsigned int>(viewPortWidth / aspect_ratio);
        viewPortYOffset = (height - viewPortHeight) / 2;
    }
    RenderEngine::Renderer::setViewport(viewPortWidth, viewPortHeight, viewPortXOffset, viewPortYOffset);
}
