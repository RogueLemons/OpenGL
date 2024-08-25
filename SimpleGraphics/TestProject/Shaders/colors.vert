#version 450 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
// layout (location = 2) in vec2 aTexCoords;

layout (location = 0) out vec3 vertColor;
// layout (location = 2) out vec2 TexCoords;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    vertColor = aColor;
}