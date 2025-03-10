#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

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
void enableWireFrame(GLFWwindow* window, bool enable);

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

    //ImGui Init
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    float deltaTime = 0.0f;
    float lastFrameTime = 0.0f;

    double previousTime = glfwGetTime();
    int frames = 0;
    static int fps = 0;

    Shader shader("assets/shaders/vertex.vert", "assets/shaders/fragment.frag");
    Camera camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.0f, 0.0f, 0.0f));
    Texture textureMap("assets/textures/blockMap.png");

    Chunk c(1, glm::vec3(0.0f, 0.0f, 0.0f));

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        //ImGui Frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        //Debug Window
        ImGui::Begin("Debug Information");

        float currentFrame = (float)glfwGetTime();
        deltaTime = currentFrame - lastFrameTime;
        lastFrameTime = currentFrame;
        camera.deltaTime = deltaTime;

        frames++;
        if (currentFrame - previousTime >= 1.0)
        {
            fps = frames;
            frames = 0;
            previousTime = currentFrame;
        }
        ImGui::Text("FPS: %d", fps);
        ImGui::Text("Camera Position: ( %.2f, %.2f, %.2f )", camera.Position.x, camera.Position.y, camera.Position.z);
        ImGui::Text("Camera Speed: %.2f", camera.speed);
        ImGui::End();

        glClearColor(0.3f, 0.5f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        textureMap.Bind();
        shader.Activate();
        c.renderChunk(shader.progID);

        camera.updateCameraMatrix(75.0f, 0.05f, 100.0f);
        camera.Inputs(window);
        shader.setUniformMat("camMatrix", camera.cameraMatrix);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    c.~Chunk();
    shader.~Shader();
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

//Really Bad Performance
void enableWireFrame(GLFWwindow* window, bool enable)
{
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
    {
        if (enable)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            enable = false;
        }
        else
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            enable = true;
        }
    }
}