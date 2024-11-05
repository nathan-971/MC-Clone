#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "shader.h"
#include "texture.h"
#include "camera.h"

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
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glEnable(GL_DEPTH_TEST);

    float deltaTime = 0.0f;
    float lastFrameTime = 0.0f;

    Shader shader("assets/shaders/vertex.vert", "assets/shaders/fragment.frag");
    Camera camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.0f, 0.0f, 0.0f));

    Texture textureMap("assets/textures/blockMap.png");
    SubTexture grass_side(&textureMap, 0, 16, 16, 16);
    SubTexture grass_bottom(&textureMap, 16, 16, 16, 16);
    SubTexture grass_top(&textureMap, 0, 0, 16, 16);

    float vertices[] = {
        // Positions          // Texture Coordinates
        // Back face
        -0.5f, -0.5f, -0.5f,  grass_side.uvCoords[0][0], grass_side.uvCoords[0][1], // Back bottom left
         0.5f, -0.5f, -0.5f,  grass_side.uvCoords[1][0], grass_side.uvCoords[1][1], // Back bottom right
         0.5f,  0.5f, -0.5f,  grass_side.uvCoords[2][0], grass_side.uvCoords[2][1], // Back top right
        -0.5f,  0.5f, -0.5f,  grass_side.uvCoords[3][0], grass_side.uvCoords[3][1], // Back top left

        // Front face
        -0.5f, -0.5f,  0.5f,  grass_side.uvCoords[0][0], grass_side.uvCoords[0][1], // Front bottom left
         0.5f, -0.5f,  0.5f,  grass_side.uvCoords[1][0], grass_side.uvCoords[1][1], // Front bottom right
         0.5f,  0.5f,  0.5f,  grass_side.uvCoords[2][0], grass_side.uvCoords[2][1], // Front top right
        -0.5f,  0.5f,  0.5f,  grass_side.uvCoords[3][0], grass_side.uvCoords[3][1], // Front top left

        // Left face
        -0.5f, -0.5f, -0.5f,  grass_side.uvCoords[0][0], grass_side.uvCoords[0][1], // Back bottom left
        -0.5f, -0.5f,  0.5f,  grass_side.uvCoords[1][0], grass_side.uvCoords[1][1], // Front bottom left
        -0.5f,  0.5f,  0.5f,  grass_side.uvCoords[2][0], grass_side.uvCoords[2][1], // Front top left
        -0.5f,  0.5f, -0.5f,  grass_side.uvCoords[3][0], grass_side.uvCoords[3][1], // Back top left

        // Right face
         0.5f, -0.5f, -0.5f,  grass_side.uvCoords[0][0], grass_side.uvCoords[0][1], // Back bottom right
         0.5f, -0.5f,  0.5f,  grass_side.uvCoords[1][0], grass_side.uvCoords[1][1], // Front bottom right
         0.5f,  0.5f,  0.5f,  grass_side.uvCoords[2][0], grass_side.uvCoords[2][1], // Front top right
         0.5f,  0.5f, -0.5f,  grass_side.uvCoords[3][0], grass_side.uvCoords[3][1], // Back top right

         // Top face
         -0.5f,  0.5f, -0.5f, grass_top.uvCoords[0][0], grass_top.uvCoords[0][1], // Back top left
          0.5f,  0.5f, -0.5f, grass_top.uvCoords[1][0], grass_top.uvCoords[1][1], // Back top right
          0.5f,  0.5f,  0.5f, grass_top.uvCoords[2][0], grass_top.uvCoords[2][1], // Front top right
         -0.5f,  0.5f,  0.5f, grass_top.uvCoords[3][0], grass_top.uvCoords[3][1], // Front top left

         // Bottom face
         -0.5f, -0.5f, -0.5f, grass_bottom.uvCoords[0][0], grass_bottom.uvCoords[0][1], // Back bottom left
          0.5f, -0.5f, -0.5f, grass_bottom.uvCoords[1][0], grass_bottom.uvCoords[1][1], // Back bottom right
          0.5f, -0.5f,  0.5f, grass_bottom.uvCoords[2][0], grass_bottom.uvCoords[2][1], // Front bottom right
         -0.5f, -0.5f,  0.5f, grass_bottom.uvCoords[3][0], grass_bottom.uvCoords[3][1]  // Front bottom left
    };

    unsigned int indices[] = {
        0, 1, 2, 
        2, 3, 0,    // Back face
        
        4, 5, 6, 
        6, 7, 4,    // Front face
       
        8, 9, 10, 
        10, 11, 8,  // Left face
        
        12, 13, 14, 
        14, 15, 12, // Right face
        
        16, 17, 18, 
        18, 19, 16, // Top face
        
        20, 21, 22, 
        22, 23, 20  // Bottom face
    };

    unsigned int VBO, EBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = (float)glfwGetTime();
        deltaTime = currentFrame - lastFrameTime;
        lastFrameTime = currentFrame;
        camera.deltaTime = deltaTime;

        glClearColor(0.3f, 0.5f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        textureMap.Bind();
        shader.Activate();

        camera.updateCameraMatrix(75.0f, 0.05f, 100.0f);
        camera.Inputs(window);
        shader.setUniformMat("camMatrix", camera.cameraMatrix);

        glBindVertexArray(VAO);
        for (int x = 0; x < 12; x++)
        {
            for (int y = 0; y < 12; y++)
            {
                for (int z = 0; z < 12; z++)
                {
                    glm::mat4 model = glm::mat4(1.0f);
                    model = glm::translate(model, glm::vec3(x, y, z));
                    shader.setUniformMat("model", model);
                    glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, nullptr);
                }
            }
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    shader.~Shader();
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}