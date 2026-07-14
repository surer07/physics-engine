#version 330 core
in vec2 TexCoord;

uniform sampler2D texture1;
uniform vec4 color;  // Make sure this exists

out vec4 FragColor;

void main()
{
    FragColor = texture(texture1, TexCoord) * color;
}