// OpenGL
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// STL
#include <iostream>
#include <chrono>

// My classes
#include "Game/Game.h"
#include "Manager/ResourceManager.h"

// Math
#include <glm/vec2.hpp>

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void WindowResizeCallback(GLFWwindow* window, int width, int height);

glm::ivec2 g_WindowSize = glm::ivec2(640, 480);
Game g_Game = Game(g_WindowSize);

int main(int argc, char* argv[])
{
    /* Initialize the library */
    if (!glfwInit()){
        std::cerr << "GLFW init failed!\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(g_WindowSize.x, g_WindowSize.y, "Hello World", NULL, NULL);
    if (!window)
    {
        std::cerr << "glfwCreateWindow failed!\n";
        glfwTerminate();
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, WindowResizeCallback);
    glfwSetKeyCallback(window, KeyCallback);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (!gladLoadGL())
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // ResourceManager init
    ResourceManager::setExecutablePath(argv[0]);

    //Game init
    if (!g_Game.init())
    {
        std::cerr << "Couldn't init game!\n";
        return -1;
    }

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

        g_Game.update(duration);
        g_Game.render();

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
    g_Game.setKey(key, action);
}

void WindowResizeCallback(GLFWwindow* window, int width, int height)
{
    g_WindowSize.x = width;
    g_WindowSize.y = height;
    glViewport(0, 0, g_WindowSize.x , g_WindowSize.y);
}
