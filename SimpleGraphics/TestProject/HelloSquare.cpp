#include "HelloSquare.h"
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


static void RunFrame(const std::function<void()>& frameFunction) {
    Charis::StartFrame();
    frameFunction();
    Charis::EndFrame();
}

struct VertexAttributes {
    glm::vec3 ver;
    glm::vec3 rgb;
    glm::vec2 tex;
};

template<class V>
static Charis::ModelComponent CreateModelFromStructs(const std::vector<V>& vertices, const std::vector<Charis::TriangleIndices> indices, const std::vector<unsigned int>& floatsPerAttributePerVertex)
{
    static_assert(sizeof(Charis::TriangleIndices) == 3 * sizeof(float));
    auto indexArray = reinterpret_cast<const unsigned int*>(indices.data());
    auto indexCount = static_cast<unsigned int>(3 * indices.size());

    unsigned int floatsPerVertex = std::reduce(floatsPerAttributePerVertex.begin(), floatsPerAttributePerVertex.end());
    Charis::Helper::RuntimeAssert(sizeof(V) == sizeof(float) * floatsPerVertex, "Number of floats in simple vertex struct must match number of attribute floats.");
    auto vertexArray = reinterpret_cast<const float*>(vertices.data());
    auto vertexCount = static_cast<unsigned int>(floatsPerVertex * vertices.size());

    return Charis::ModelComponent(vertexArray, vertexCount, indexArray, indexCount, floatsPerAttributePerVertex);
}

void HelloSquare() {
    Charis::Initialize(800, 600, "Hello Square!");

    const auto vertices = std::vector<VertexAttributes>{
        // Position             // Color                // Texture coord
      { { -0.5f, -0.5f, 0.0f }, {  1.0f,  0.0f, 0.0f }, { 0.0f, 0.0f } },
      { {  0.5f, -0.5f, 0.0f }, {  0.0f,  1.0f, 0.0f }, { 1.0f, 0.0f } },
      { {  0.5f,  0.5f, 0.0f }, {  0.0f,  0.0f, 1.0f }, { 1.0f, 1.0f } },
      { { -0.5f,  0.5f, 0.0f }, {  1.0f,  1.0f, 1.0f }, { 0.0f, 1.0f } }
    };
    const auto indices = std::vector<Charis::TriangleIndices>{
        { 0, 1, 2 },
        { 0, 3, 2 }
    };

    const auto square = CreateModelFromStructs(vertices, indices, { 3, 3, 2 });
    const auto shader = Charis::Shader("Shaders/hello_square.vert", "Shaders/hello_square.frag");
    const auto container = Charis::Texture("Images/container2.png");

    const auto textureBinding = 0;
    shader.SetTexture("tex", textureBinding);
    container.BindTo(textureBinding);

    while (Charis::WindowIsOpen()) { RunFrame([&]() {

            if (Charis::Input::KeyState(Charis::Input::Escape, Charis::Input::Pressed))
                Charis::Utility::CloseWindow();

            shader.Draw(square);

    }); }

    Charis::CleanUp();
}