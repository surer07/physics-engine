#include "component_storage.h"
#include "entity_manager.h"
#include "components/sprite.h"
#include "components/transform.h"

class Registry
{
private:
    EntityManager entity_manager;

    // All your component pools sit here
    // example:
    ComponentStorage<Sprite> sprites;
    ComponentStorage<Transform> transforms;

public:
    Entity create_entity();
    void destroy_entity(Entity entity);

    template <typename T>
    ComponentStorage<T> &get_storage()
    {
        if constexpr (std::is_same_v<T, Sprite>)
            return sprites;
        if constexpr (std::is_same_v<T, Transform>)
            return transforms;
    }

    template <typename T>
    void assign(Entity entity, T component);
};