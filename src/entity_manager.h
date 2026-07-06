#pragma once

#include <vector>
#include <cstdint>

struct Entity
{
    uint32_t id;

    uint32_t index() const;
    uint32_t generation() const;
};

class EntityManager
{
private:
    std::vector<uint32_t> generations;
    std::vector<uint32_t> free_indices;

public:
    Entity create();
    void destroy(Entity entity);
    bool is_valid(Entity entity) const;
};