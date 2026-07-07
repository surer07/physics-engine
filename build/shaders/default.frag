#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D imageTexture; // Set up automatically by default slot GL_TEXTURE0

void main() {
    vec4 texColor = texture(imageTexture, TexCoord);
    
    // Transparent clipping discard optimization for 2D sprites
    if(texColor.a < 0.1) {
        discard;
    }
    
    FragColor = texColor;
}