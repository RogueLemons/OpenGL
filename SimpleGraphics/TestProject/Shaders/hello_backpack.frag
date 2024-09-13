#version 450 core

// Input
layout (location = 0) in vec3 inFragPos;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inTexCoords;
// Output
layout (location = 0) out vec4 outFragColor;

// Texture uniforms
uniform sampler2D DiffuseTexture_1;
uniform sampler2D SpecularTexture_1;
uniform sampler2D HeightTexture_1;

void main()
{
    vec4 diffuseColor = texture(DiffuseTexture_1, inTexCoords);
    vec4 specularColor = texture(SpecularTexture_1, inTexCoords);
    vec4 heightColor = texture(HeightTexture_1, inTexCoords);
    outFragColor = diffuseColor;
}