#version 450 core

// Input
layout (location = 0) in vec3 inWorldFrag;
layout (location = 1) in vec3 inWorldNormal;
layout (location = 2) in vec2 inTexCoords;
// Output
layout (location = 0) out vec4 outFragColor;

// Uniform - textures
uniform sampler2D DiffuseTexture_1;
uniform sampler2D SpecularTexture_1;
uniform sampler2D HeightTexture_1;

// Uniform - camera position
uniform vec3 cameraPos;

// Uniform - directional light
struct DirectionalLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform DirectionalLight dirLight;

void main()
{
    vec3 heightColor = vec3(texture(HeightTexture_1, inTexCoords));

    // Properties
    vec3 diffuseColor = vec3(texture(DiffuseTexture_1, inTexCoords));
    vec3 specularColor = vec3(texture(SpecularTexture_1, inTexCoords));
    vec3 normal = normalize(inWorldNormal);
    vec3 viewDir = normalize(cameraPos - inWorldFrag);
    vec3 lightDir = normalize(-dirLight.direction);
    
    // ambient
    vec3 ambient = dirLight.ambient * diffuseColor;
    // diffuse
    float diffuseStrength = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diffuseStrength * dirLight.diffuse * diffuseColor;
    // specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float specularStrength = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * dirLight.specular * specularColor;
    
    // total
    outFragColor = vec4(ambient + diffuse + specular, 1.0);
}