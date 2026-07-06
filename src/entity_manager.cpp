#include "entity_manager.h"

uint32_t Entity::index() const
{
    return id & 0xFFFFFF;
}

uint32_t Entity::generation() const
{
    return id >> 24;
}

Entity EntityManager::create()
{
    uint32_t index;
    uint32_t generation;

    if (!free_indices.empty())
    {
        // Recycle an old slot
        index = free_indices.back();
        free_indices.pop_back();
        generation = generations[index]; // Use the already incremented generation
    }
    else
    {
        // Create a brand new slot
        index = static_cast<uint32_t>(generations.size());
        generation = 1; // Start generations at 1
        generations.push_back(generation);
    }

    // Pack index and generation into the single 32-bit ID
    uint32_t id = (generation << 24) | index;
    return Entity{id};
}

void EntityManager::destroy(Entity entity)
{
    uint32_t idx = entity.index();

    // Safety check: Is this entity even valid?
    if (idx >= generations.size() || generations[idx] != entity.generation())
    {
        return;
    }

    // Increment the generation inside the slot so old IDs become invalid
    // Mask with 0xFF to ensure it rolls over safely at 255 back to 0
    generations[idx] = (generations[idx] + 1) & 0xFF;

    // Mark the index as free to reuse
    free_indices.push_back(idx);
}

bool EntityManager::is_valid(Entity entity) const
{
    uint32_t idx = entity.index();
    return idx < generations.size() && generations[idx] == entity.generation();
}
