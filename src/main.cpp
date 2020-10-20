#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "Renderer/ShaderProgram.h"
#include "Renderer/Texture2D.h"
#include "Manager/ResourceManager.h"
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



{
    ResourceManager resManager(argv[0]);
    std::shared_ptr<Renderer::ShaderProgram> shaderProgram =
        resManager.loadShaders("FirstProgram",
                               "resource/shaders/vertex.vs",
                               "resource/shaders/fragment.fs");

    std::shared_ptr<Renderer::Texture2D> myTexture =
        resManager.loadTexture("FirstTexture",
                               "resource/textures/map_16x16.png");


    GLfloat vertexData[] = {
        //vertices          //color             //texture
        0.f,   50.f, 0.0f,  1.0f, 0.0f, 0.0f,   0.5f, 1.0f,
        50.f, -50.f, 0.0f,  0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
       -50.f, -50.f, 0.0f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f
    };

    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), nullptr);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (void*)(3*sizeof(GL_FLOAT)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (void*)(6 * sizeof(GL_FLOAT)));

    glm::mat4 projectionMatrix = glm::ortho(0.0f, (float)g_SCREEN_WIDTH,
                                            0.0f, (float)g_SCREEN_HEIGHT,
                                            100.0f, -100.0f);

    glm::mat4 modelMatrix_1 = glm::mat4(1.0f);
    modelMatrix_1 = glm::translate(modelMatrix_1, glm::vec3(100.0f, 50.0f, 0.0f));

    glm::mat4 modelMatrix_2 = glm::mat4(1.f);
    modelMatrix_2 = glm::translate(modelMatrix_2, glm::vec3(g_SCREEN_WIDTH/2.f, g_SCREEN_HEIGHT/2.f, 0.f));


    shaderProgram->Use();
    shaderProgram->setUniform("projectionMatrix", projectionMatrix);

    shaderProgram->setUniform("myTexture", 0);
    glClearColor(0.5f, 0.25f, 0, 1);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        glBindVertexArray(vao);
        shaderProgram->Use();
        myTexture->bind();
        shaderProgram->setUniform("modelMatrix", modelMatrix_1);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        shaderProgram->setUniform("modelMatrix", modelMatrix_2);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        myTexture->unbind();
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
}
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
