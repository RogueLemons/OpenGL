#include "HelloTriangle.h"
#include <iostream>
#include <vector>
#include <functional>
#include <numeric>

// Charis
#include "Charis/Initialize.h"
#include "Charis/Utility.h"
#include "Charis/Model.h"
#include "Charis/Shader.h"

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

template<class V>
static Charis::Model CreateModelFromStructs(const std::vector<V>& vertices, const std::vector<unsigned int>& floatsPerAttributePerVertex)
{
    unsigned int floatsPerVertex = std::reduce(floatsPerAttributePerVertex.begin(), floatsPerAttributePerVertex.end());
    Charis::Helper::RuntimeAssert(sizeof(V) == sizeof(float) * floatsPerVertex, "Number of floats in simple vertex struct must match number of attribute floats.");
    return Charis::Model(reinterpret_cast<const float*>(vertices.data()), static_cast<unsigned int>(floatsPerVertex * vertices.size()), floatsPerAttributePerVertex);
}

void HelloTriangle() {
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

