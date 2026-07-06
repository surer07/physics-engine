#pragma once
#include <cstdint>

struct Sprite
{
    uint32_t texture_id{0};
    uint32_t shader_id{0}; // Determines which shader to use
    float color[4]{1.0f, 1.0f, 1.0f, 1.0f};
};