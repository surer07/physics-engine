#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "game.h"

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

    double t_last = glfwGetTime(); // Fix: Initialize properly with current time
    float t_accumulator = 0.0f;
    float step = 0.01f; // 100 FPS fixed physics updates

    while (!glfwWindowShouldClose(window))
    {
        // A. MUST poll OS events at the beginning of the frame
        glfwPollEvents();

        double t_current = glfwGetTime();
        float dt = static_cast<float>(t_current - t_last);
        t_last = t_current;

        // Cap dt to prevent "spiral of death" if the game lags heavily
        if (dt > 0.25f)
            dt = 0.25f;

        t_accumulator += dt;

        while (t_accumulator >= step)
        {
            // B. Pass input state to your ECS game instance right before systems update
            game.process_input(keys);

            // Run your physics and movement systems with a fixed dt
            game.update(step);
            t_accumulator -= step;
        }

        // C. Render and swap buffers exactly ONCE per frame (outside the fixed update loop)
        glClear(GL_COLOR_BUFFER_BIT); // Clear screen before drawing next frame
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}