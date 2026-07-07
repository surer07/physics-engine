#include "../registry.h"
#include "../components/transform.h"
#include "../components/sprite.h"
#include <glad/glad.h>
#include <cmath>

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

            // Calculate Model Matrix for a top-left origin quad
            // Note: Since our Quad VAO vertices run from -0.5 to 0.5,
            // shifting by (+0.5, +0.5) inside translation aligns its top-left corner perfectly to (x, y)
            float radians = transform.rotation * 0.0174532925f; // Convert degrees to radians
            float cos_r = std::cos(radians);
            float sin_r = std::sin(radians);

            float scale_x = transform.scale.x;
            float scale_y = transform.scale.y;

            // Compute standard column-major transform matrix
            float model[16] = {
                cos_r * scale_x, sin_r * scale_x, 0.0f, 0.0f,
                -sin_r * scale_y, cos_r * scale_y, 0.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f,
                transform.position.x, transform.position.y, 0.0f, 1.0f};

            // Locate the "model" variable location inside the current active shader
            int model_loc = glGetUniformLocation(current_shader, "model");
            if (model_loc != -1)
            {
                glUniformMatrix4fv(model_loc, 1, GL_FALSE, model);
            }

            glDrawArrays(GL_TRIANGLES, 0, 6);
        }
    }
    glBindVertexArray(0);
}