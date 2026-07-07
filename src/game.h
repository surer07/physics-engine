#include "registry.h"
#include "systems/render_context.cpp"
#include "systems/render_system.cpp"

class Game
{
private:
    Registry registry;
    RenderContext renderContext;

public:
    Game();
    ~Game();

    void process_input(const bool *keys_state);
    void update(float dt);
};
