#include "game.h"

Game::Game()
{
    renderContext.init();
}

Game::~Game()
{
}

void Game::update(double time)
{
    while (running)
    {
        float dt = time - t_last;
        t_last += dt;
        t_accumulator += dt;
        while (t_accumulator > step)
        {
            // systems

            t_accumulator -= step;
        }
        // draw
    }
}
