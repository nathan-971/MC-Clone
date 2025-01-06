#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "shader.h"
#include "texture.h"
#include "camera.h"
#include "chunk.h"

#define VSYNC 1
#define NOVSYNC 0

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "GLCraft", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(VSYNC);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);

    float deltaTime = 0.0f;
    float lastFrameTime = 0.0f;

    double previousTime = glfwGetTime();
    int frames = 0;

    Shader shader("assets/shaders/vertex.vert", "assets/shaders/fragment.frag");
    Camera camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.0f, 0.0f, 0.0f));
    Texture textureMap("assets/textures/blockMap.png");

    Chunk c(8, glm::vec3(0.0f, 0.0f, 0.0f));

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = (float)glfwGetTime();
        deltaTime = currentFrame - lastFrameTime;
        lastFrameTime = currentFrame;
        camera.deltaTime = deltaTime;

        frames++;
        if (currentFrame - previousTime >= 1.0)
        {
            std::cout << "FPS: " << frames << std::endl;
            frames = 0;
            previousTime = currentFrame;
        }

        glClearColor(0.3f, 0.5f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        textureMap.Bind();
        shader.Activate();
        c.renderChunk(shader.progID);

        camera.updateCameraMatrix(75.0f, 0.05f, 100.0f);
        camera.Inputs(window);
        shader.setUniformMat("camMatrix", camera.cameraMatrix);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    c.~Chunk();
    shader.~Shader();
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}