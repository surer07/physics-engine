#include "registry.h"

Entity Registry::create_entity()
{
    return entity_manager.create();
}

void Registry::destroy_entity(Entity entity)
{
    // 1. Safety First: Ensure the entity is actually alive right now
    if (!entity_manager.is_valid(entity))
    {
        return;
    }

    // 2. Remove the entity's data from all component pools
    // This triggers the Swap-and-Pop mechanism we built
    // examples:
    // rigid_bodies.remove(entity);

    // 3. Finally, tell the entity manager to increment the generation
    // and put the index into the free list
    entity_manager.destroy(entity);
}

// Forward the component to the correct sparse set storage
template <typename T>
void Registry::assign(Entity entity, T component)
{
    get_storage<T>().insert(entity, component);
}

// !TODO:
// unassign component to an entity