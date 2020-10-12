#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "Renderer/ShaderProgram.h"

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void WindowResizeCallback(GLFWwindow* window, int width, int height);

int g_SCREEN_WIDTH = 640;
int g_SCREEN_HEIGHT = 480;

int main(void)
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
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;


    const char* vertexShader =
    "#version 330 core\n"
    "layout(location = 0) in vec3 vertex_position;\n"
    "layout(location = 1) in vec3 vertex_color;\n"
    "out vec3 color;\n"
    "void main(){\n"
    "   color = vertex_color;\n"
    "   gl_Position = vec4(vertex_position, 1.0);\n"
    "}\0";

    const char* fragmentShader =
    "#version 330 core\n"
    "in vec3 color;\n"
    "out vec4 FragColor;\n"
    "void main(){\n"
    "   FragColor = vec4(color, 1.0);\n"
    "}\0";
    std::string vertexSh = vertexShader;
    std::string fragSha = fragmentShader;

    Renderer::ShaderProgram shaderProg(vertexSh, fragSha);

    GLfloat vertexData[] = {
        //vertices          //colors
       -0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
        0.0f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
       -1.0f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,
        0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,
        1.0f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
        0.0f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GL_FLOAT), nullptr);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GL_FLOAT), (void*)(3*sizeof(GL_FLOAT)));

    glViewport(g_SCREEN_WIDTH / 2, g_SCREEN_HEIGHT / 2, g_SCREEN_WIDTH/2, g_SCREEN_HEIGHT/2);
    glClearColor(1,1,0,1);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProg.Use();
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
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
    glViewport(g_SCREEN_WIDTH / 2, g_SCREEN_HEIGHT / 2, g_SCREEN_WIDTH/2, g_SCREEN_HEIGHT/2);
}
