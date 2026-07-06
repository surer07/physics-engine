#include "component_storage.h"
#include "entity_manager.h"

class Registry
{
private:
    EntityManager entity_manager;

    // All your component pools sit here
    // example:
    // ComponentStorage<RigidBody> rigid_bodies;

public:
    Entity create_entity();
    void destroy_entity(Entity entity);

    template <typename T>
    ComponentStorage<T> &get_storage();

    template <typename T>
    void assign(Entity entity, T component);
};