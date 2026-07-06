#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "game.h" // Assuming Game class is defined here

// Array tracking state of every key (true if pressed)
bool keys[1024] = {false};

// GLFW Key Callback function
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
        {
            keys[key] = true;
        }
        else if (action == GLFW_RELEASE)
        {
            keys[key] = false;
        }
    }
}

int main()
{
    // 1. Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Configure window hints for core profile OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 2. Create Window
    GLFWwindow *window = glfwCreateWindow(800, 600, "2D ECS Engine", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Set input callback
    glfwSetKeyCallback(window, key_callback);

    // 3. Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Configure viewport and blending for 2D sprites
    glViewport(0, 0, 800, 600);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // 4. Instantiate and Initialize Game
    Game game;

    // Timing variables
    float delta_time = 0.0f;
    float last_frame = 0.0f;

    // 5. Main Game Loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        game.update(static_cast<float>(glfwGetTime()));

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}