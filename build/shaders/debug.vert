#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec3 aColor;

out vec3 Color;

uniform mat4 model;

layout(std140) uniform CameraData
{
    mat4 projection;
};

void main()
{
    Color = aColor;
    gl_Position = projection * model * vec4(aPos, 0.0, 1.0);
}