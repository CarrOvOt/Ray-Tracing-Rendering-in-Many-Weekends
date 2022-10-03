// GLFW and GLAD
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// ImGUI
#include <ImGUI/imgui.h>
#include <ImGUI/imgui.h>
#include <ImGUI/imgui_impl_glfw.h>
#include <ImGUI/imgui_impl_opengl3.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/random.hpp >

// others
#include <iostream>
#include <memory>
#include <string>

// our code
#include "shader.h"
#include "camera.h"


// settings
static unsigned int SCR_WIDTH = 1280;
static unsigned int SCR_HEIGHT = 720;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

static const float QuadVertices[] = {
    // positions          
    -1.0f,  1.0f, 0.0f,
    -1.0f, -1.0f, 0.0f,
     1.0f, -1.0f, 0.0f,
     1.0f, -1.0f, 0.0f,
     1.0f,  1.0f, 0.0f,
    -1.0f,  1.0f, 0.0f,
};


glm::vec3 RayColor(const Ray r) {
    float t = 0.5 * (r.dir.y/abs(r.dir.z) + 1.0);
    return  glm::vec3(1.0, 1.0, 1.0) * (1.0f - t) + glm::vec3(0.5, 0.7, 1.0) * t;
}


int main() {

    // initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_RESIZABLE, false);// fix window size
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // create a window
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "RayTracingR", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);


    // initialize GLAD *AFTER* creating a GLFWindow
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    const char* version = (const char*)glGetString(GL_VERSION);
    printf("OpenGL version : %s\n", version);


    // screen mesh and shader
    unsigned int VAO, VBO;
    // bind vertices
    {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(QuadVertices), &QuadVertices, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    }
    Shader shader("screen.vert","screen.frag");



    // screen pixel color
    float* pixels = (float*)malloc(sizeof(float) * SCR_HEIGHT * SCR_WIDTH * 3);

    // screen texture
    unsigned int texture = 0;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_FLOAT, pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);


    Camera mainCamera(SCR_HEIGHT,SCR_WIDTH);


    // rendering loop
    int i = 0;
    while (!glfwWindowShouldClose(window)) {

        i++;

        // timing
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // gl settings
        glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        for (int y = 0; y < SCR_HEIGHT; ++y) {
            for (int x = 0; x < SCR_WIDTH; ++x) {

                glm::vec3 color = RayColor(mainCamera.GetPixelRay(x, y));

                pixels[y * SCR_WIDTH * 3 + x * 3 + 0] = color.x;
                pixels[y * SCR_WIDTH * 3 + x * 3 + 1] = color.y;
                pixels[y * SCR_WIDTH * 3 + x * 3 + 2] = color.z;
            }
        }


        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, SCR_WIDTH, SCR_HEIGHT, GL_RGB, GL_FLOAT, pixels);

        // draw screen mesh
        shader.use();

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);




        glfwSwapBuffers(window);
        glfwPollEvents();
    }






    // release resource and quit
    glDeleteTextures(1, &texture);
    free(pixels);

    glfwTerminate();



    return 0;
}


