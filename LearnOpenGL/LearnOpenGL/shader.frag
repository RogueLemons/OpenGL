#version 450 core

layout (location = 0) in vec3 ourColor;
layout (location = 1) in vec2 TexCoord;

layout (location = 0) out vec4 FragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    // FragColor = vec4(ourColor, 1.0f);
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
}