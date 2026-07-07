#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

// This layout configuration hooks up directly to UBO binding point slot 0
layout (std140) uniform CameraData {
    mat4 projection;
};

uniform mat4 model;

void main() {
    // Offset the base -0.5 to 0.5 quad vertices so that tracking origin is top-left (0,0)
    vec4 localPos = vec4(aPos + vec2(0.5, 0.5), 0.0, 1.0);
    
    // Matrix multiplication order is critical: Projection * Model * Vertex Position
    gl_Position = projection * model * localPos;
    TexCoord = aTexCoord;
}