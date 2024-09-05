#version 450 core

layout (location = 0) in vec3 vertColor;
layout (location = 1) in vec2 texCoords;

layout (location = 0) out vec4 fragColor;

uniform sampler2D DiffuseTexture_1;

void main()
{
    vec4 color = vec4(vertColor, 1.0);
    vec4 texColor = texture(DiffuseTexture_1, texCoords);
    fragColor = mix(color, texColor, 0.5);
}