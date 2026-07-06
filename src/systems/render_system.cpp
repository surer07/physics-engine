#include "../registry.h"
#include "../components/transform.h"
#include "../components/sprite.h"
#include <glad/glad.h>

void render_system(Registry &registry, uint32_t quad_vao)
{
    auto &sprite_storage = registry.get_storage<Sprite>();
    auto &transform_storage = registry.get_storage<Transform>();

    glBindVertexArray(quad_vao);

    uint32_t current_shader = 0; // Track active shader

    for (size_t i = 0; i < sprite_storage.dense_components.size(); ++i)
    {
        Entity entity = sprite_storage.dense_entities[i];

        if (transform_storage.has(entity))
        {
            Sprite &sprite = sprite_storage.dense_components[i];
            Transform &transform = transform_storage.get(entity);

            // Swap shader only if it's different from the currently bound one
            if (sprite.shader_id != current_shader)
            {
                glUseProgram(sprite.shader_id);
                current_shader = sprite.shader_id;
            }

            glBindTexture(GL_TEXTURE_2D, sprite.texture_id);

            // TODO: Pass transform matrix to the current shader via glUniformMatrix4fv

            glDrawArrays(GL_TRIANGLES, 0, 6);
        }
    }
    glBindVertexArray(0);
}