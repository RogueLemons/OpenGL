#include <iostream>
#include <vector>
#include <functional>
#include <numeric>

// Charis
#include "Charis/Initialize.h"
#include "Charis/Utility.h"
#include "Charis/Model.h"
#include "Charis/Shader.h"
#include "Charis/Texture.h"

// Libraries
#include <glm/glm.hpp>

static void RunFrame(const std::function<void()>& frameFunction) {
    Charis::StartFrame();
    frameFunction();
    Charis::EndFrame();
}

struct Vertex {
    float x{};
    float y{};
    float z{};
};

struct VertexAttributes {
    glm::vec3 ver;
    glm::vec3 rgb;
    glm::vec2 tex;
};

template<class V>
static Charis::Model CreateModelFromStructs(const std::vector<V>& vertices, const std::vector<unsigned int>& floatsPerAttributePerVertex)
{
    unsigned int floatsPerVertex = std::reduce(floatsPerAttributePerVertex.begin(), floatsPerAttributePerVertex.end());
    Charis::Helper::RuntimeAssert(sizeof(V) == sizeof(float) * floatsPerVertex, "Number of floats in simple vertex struct must match number of attribute floats.");
    return Charis::Model(reinterpret_cast<const float*>(vertices.data()), static_cast<unsigned int>(floatsPerVertex * vertices.size()), floatsPerAttributePerVertex);
}

template<class V>
static Charis::Model CreateModelFromStructs(const std::vector<V>& vertices, const std::vector<Charis::TriangleIndices> indices, const std::vector<unsigned int>& floatsPerAttributePerVertex)
{
    static_assert(sizeof(Charis::TriangleIndices) == 3 * sizeof(float));
    auto indexArray = reinterpret_cast<const unsigned int*>(indices.data());
    auto indexCount = static_cast<unsigned int>(3 * indices.size());

    unsigned int floatsPerVertex = std::reduce(floatsPerAttributePerVertex.begin(), floatsPerAttributePerVertex.end());
    Charis::Helper::RuntimeAssert(sizeof(V) == sizeof(float) * floatsPerVertex, "Number of floats in simple vertex struct must match number of attribute floats.");
    auto vertexArray = reinterpret_cast<const float*>(vertices.data());
    auto vertexCount = static_cast<unsigned int>(floatsPerVertex * vertices.size());

    return Charis::Model(vertexArray, vertexCount, indexArray, indexCount, floatsPerAttributePerVertex);
}

static void HelloTriangle() {
    Charis::Initialize(800, 600, "Hello Triangle!");

    const std::vector<Vertex> vertices = {
        { -0.5f, -0.5f, 0.0f },
        {  0.5f, -0.5f, 0.0f },
        {  0.0f,  0.5f, 0.0f }
    };
    const auto triangle = CreateModelFromStructs(vertices, { 3 });

    const char* vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";
    const char* fragmentShaderSource = "#version 330 core\n"
        "layout (location = 0) out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0";
    const auto shader = Charis::Shader(vertexShaderSource, fragmentShaderSource, Charis::Shader::InCode);


    while (Charis::WindowIsOpen()) { RunFrame([&]() {

        if (Charis::Input::KeyState(Charis::Input::Escape, Charis::Input::Pressed))
            Charis::Utility::CloseWindow();

        shader.Draw(triangle);

    }); }

    Charis::CleanUp();
}

static void HelloSquare() {
    Charis::Initialize(800, 600, "Hello Square!");

    const std::vector<VertexAttributes> vertices = {
          // Position             // Color                // Texture coord
        { { -0.5f, -0.5f, 0.0f }, {  1.0f,  0.0f, 0.0f }, { 0.0f, 0.0f } },
        { {  0.5f, -0.5f, 0.0f }, {  0.0f,  1.0f, 0.0f }, { 1.0f, 0.0f } },
        { {  0.5f,  0.5f, 0.0f }, {  0.0f,  0.0f, 1.0f }, { 1.0f, 1.0f } },
        { { -0.5f,  0.5f, 0.0f }, {  1.0f,  1.0f, 1.0f }, { 0.0f, 1.0f } }
    };
    const std::vector<Charis::TriangleIndices> indices = {
        { 0, 1, 2 },
        { 0, 3, 2 }
    };

    const auto triangle = CreateModelFromStructs(vertices, indices, { 3, 3, 2 });
    const auto shader = Charis::Shader("Shaders/colors.vert", "Shaders/colors.frag");

    int textureBinding = 0;
    const auto texture = Charis::Texture("Images/container2.png", textureBinding);
    shader.SetTexture("tex", textureBinding);

    while (Charis::WindowIsOpen()) { RunFrame([&]() {

        if (Charis::Input::KeyState(Charis::Input::Escape, Charis::Input::Pressed))
            Charis::Utility::CloseWindow();

        shader.Draw(triangle);

    }); }

    Charis::CleanUp();
}

int main()
{
    HelloTriangle();

    HelloSquare();
   
    return 0;
}