#version 450 core

layout (location = 1) in vec2 texCoords;

layout (location = 0) out vec4 fragColor;

uniform sampler2D DiffuseTexture_1;
uniform sampler2D SpecularTexture_1;
uniform sampler2D HeightTexture_1;

void main()
{
    vec4 diffuseColor = texture(DiffuseTexture_1, texCoords);
    vec4 specularColor = texture(SpecularTexture_1, texCoords);
    vec4 heightColor = texture(HeightTexture_1, texCoords);
    fragColor = diffuseColor;
}