#include <vector>
#include <cstdint>
#include "entity_manager.h"

// A sentinel value meaning "this entity does not have this component"
const uint32_t INVALID_INDEX = 0xFFFFFFFF;

class IComponentStorage
{
public:
    virtual ~IComponentStorage() = default;
    virtual void remove(Entity entity) = 0; // Pure virtual
};

template <typename T>
struct ComponentStorage : public IComponentStorage
{
    std::vector<T> dense_components;
    std::vector<Entity> dense_entities;
    std::vector<uint32_t> sparse_indices;

    void insert(Entity entity, T component);
    void remove(Entity entity) override;
    T &get(Entity entity);
    bool has(Entity entity) const;
};