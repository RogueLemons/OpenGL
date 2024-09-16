#version 450 core

// Input
layout (location = 0) in vec3 inVertex;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inTexCoords;
layout (location = 3) in vec3 inTangent;
layout (location = 4) in vec3 inBitangent;
// Output
layout (location = 0) out vec3 outWorldVertex;
layout (location = 1) out vec3 outWorldNormal;
layout (location = 2) out vec2 outTexCoords;

// Uniforms
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(inVertex.x, inVertex.y, inVertex.z, 1.0);
    outWorldVertex = vec3(model * vec4(inVertex, 1.0));
    outWorldNormal = mat3(transpose(inverse(model))) * inNormal;
    outTexCoords = inTexCoords;
}