#include "game.h"

Game::Game()
{
    renderContext.init();
    // entities
}

Game::~Game()
{
}

void Game::process_input(const bool *keys_state)
{
    // Example: Fetch your local player entity from the ECS registry
    // Entity player = get_player_entity();
    // auto &input = registry.get<InputComponent>(player);

    // Continuous Movement (Polling style using your global state array)
    // input.move_left = keys_state[GLFW_KEY_A];
    // input.move_right = keys_state[GLFW_KEY_D];

    // Discrete/One-off Actions (Edge detection)
    // To catch the exact frame a button was pressed, check if it was false last frame
    // static bool space_was_pressed = false;
    // if (keys_state[GLFW_KEY_SPACE] && !space_was_pressed)
    // {
    //     registry.add_component<JumpIntentComponent>(player);
    // }
    // space_was_pressed = keys_state[GLFW_KEY_SPACE];
}

void Game::update(float dt)
{
    // systems

    render_system(registry);
}
