#include "component_storage.h"

// Assigns a new component to an entity
template <typename T>
void ComponentStorage<T>::insert(Entity entity, T component)
{
    uint32_t ent_idx = entity.index();

    // 1. Ensure the sparse array is big enough to hold this entity's index
    if (ent_idx >= sparse_indices.size())
    {
        sparse_indices.resize(ent_idx + 1, INVALID_INDEX);
    }

    // Safety check: Does this entity already have this component?
    if (sparse_indices[ent_idx] != INVALID_INDEX)
    {
        // Update existing component instead of adding a duplicate
        dense_components[sparse_indices[ent_idx]] = component;
        return;
    }

    // 2. Find the next available index in our packed dense arrays
    uint32_t dense_idx = static_cast<uint32_t>(dense_components.size());

    // 3. Map the entity index to its new position in the dense array
    sparse_indices[ent_idx] = dense_idx;

    // 4. Push the component and the owner entity to the back of the dense lists
    dense_components.push_back(component);
    dense_entities.push_back(entity);
}

template <typename T>
void ComponentStorage<T>::remove(Entity entity)
{
    uint32_t ent_idx = entity.index();

    // 1. Safety check: Does this entity even have this component?
    if (ent_idx >= sparse_indices.size() || sparse_indices[ent_idx] == INVALID_INDEX)
    {
        return;
    }

    uint32_t dense_idx = sparse_indices[ent_idx];
    uint32_t last_dense_idx = static_cast<uint32_t>(dense_components.size() - 1);

    // 2. If it's NOT the last element, swap the last element into the deleted slot
    if (dense_idx != last_dense_idx)
    {
        // Get the entity that currently owns the last slot
        Entity last_entity = dense_entities[last_dense_idx];

        // Move the last element's data into the slot we are deleting
        dense_components[dense_idx] = std::move(dense_components[last_dense_idx]);
        dense_entities[dense_idx] = last_entity;

        // Update the moved entity's sparse index to point to its new dense location
        sparse_indices[last_entity.index()] = dense_idx;
    }

    // 3. Invalidate the sparse index of the entity we just removed
    sparse_indices[ent_idx] = INVALID_INDEX;

    // 4. Pop the back of the dense vectors (removes the duplicate data)
    dense_components.pop_back();
    dense_entities.pop_back();
}

// Quick helper to fetch a component for a given entity
template <typename T>
T &ComponentStorage<T>::get(Entity entity)
{
    uint32_t dense_idx = sparse_indices[entity.index()];
    return dense_components[dense_idx];
}

template <typename T>
bool ComponentStorage<T>::has(Entity entity) const
{
    uint32_t ent_idx = entity.index();
    return ent_idx < sparse_indices.size() && sparse_indices[ent_idx] != INVALID_INDEX;
}