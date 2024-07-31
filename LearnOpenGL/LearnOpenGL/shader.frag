#version 450 core

layout (location = 0) in vec3 ourColor;
layout (location = 1) in vec2 TexCoord;

layout (location = 0) out vec4 FragColor;

uniform sampler2D ourTexture;

void main()
{
    // FragColor = vec4(ourColor, 1.0f);
    FragColor = texture(ourTexture, TexCoord);
}