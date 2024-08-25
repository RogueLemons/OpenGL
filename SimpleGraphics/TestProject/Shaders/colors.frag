#version 450 core

layout (location = 0) in vec3 vertColor;
// layout (location = 1) in vec2 texCoords;

layout (location = 0) out vec4 fragColor;

// uniform sampler2D tex;

// Function implementation
void main()
{
    vec3 color = vertColor;
    // color += vec3(texture(tex, texCoords));
    fragColor = vec4(color, 1.0);
}
