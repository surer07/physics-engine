#include "registry.h"
#include "systems/render_context.cpp"

class Game
{
private:
    bool running = true;
    double t_last = 0.0f;
    float t_accumulator = 0.0f;
    float step = 0.01;

    Registry registry;
    RenderContext renderContext;

public:
    Game();
    ~Game();

    void update(double time);
};
