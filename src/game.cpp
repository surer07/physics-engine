#include "registry.h"

class Game
{
private:
    bool running = true;
    double t_last = 0.0f;
    float t_accumulator = 0.0f;
    float step = 0.01;

    Registry registry;

public:
    Game()
    {
    }

    ~Game()
    {
    }

    void update(double time)
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
};