#include "Camera.hpp"
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

// Settings
constexpr unsigned int SCREEN_WIDTH = 800;
constexpr unsigned int SCREEN_HEIGHT = 600;

// Functions
static void RunFrame(const std::function<void(float dt)>& frameFunction) {
    Charis::StartFrame();

    static float lastTime = Charis::Utility::GetTime();
    const auto time = Charis::Utility::GetTime();
    const auto deltaTime = time - lastTime;
    lastTime = time;

    frameFunction(deltaTime);
    Charis::EndFrame();
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

namespace ProcessInputHelperFunctions {
    static void Keyboard(Camera& camera, float deltaTime) {
        using namespace Charis::Input;

        if (KeyState(Key::W, Pressed))
            camera.ProcessKeyboard(CameraMovement::FORWARD, deltaTime);
        if (KeyState(Key::A, Pressed))
            camera.ProcessKeyboard(CameraMovement::LEFT, deltaTime);
        if (KeyState(Key::S, Pressed))
            camera.ProcessKeyboard(CameraMovement::BACKWARD, deltaTime);
        if (KeyState(Key::D, Pressed))
            camera.ProcessKeyboard(CameraMovement::RIGHT, deltaTime);
    }
    static void MousePosition(Camera& camera) {
        // Statics
        static bool noInput = true;
        static auto lastCursor = Charis::Input::CursorPosition();

        // CursorPosition gives {0, 0} until first time it is moved
        if (noInput && lastCursor.X == 0.0f && lastCursor.Y == 0.0f) {
            lastCursor = Charis::Input::CursorPosition();
            return;
        }
        if (noInput && (lastCursor.X != 0.0f || lastCursor.Y != 0.0f)) {
            noInput = false;
        }

        // Cursor delta
        const auto cursor = Charis::Input::CursorPosition();
        const auto deltaX = cursor.X - lastCursor.X;
        const auto deltaY = cursor.Y - lastCursor.Y;
        camera.ProcessMouseMovement(deltaX, -deltaY);
        lastCursor = cursor;
    }
    static void MouseScroll(Camera& camera) {
        static auto lastWheel = Charis::Input::MouseWheel();

        const auto wheel = Charis::Input::MouseWheel();
        const auto deltaWheel = wheel - lastWheel;
        camera.ProcessMouseScroll(deltaWheel);
        lastWheel = wheel;
    }
}
static void ProcessInput(Camera& camera, float deltaTime) {
    using namespace ProcessInputHelperFunctions;

    Keyboard(camera, deltaTime);
    MousePosition(camera);
    MouseScroll(camera);
}

static void HelloCameraSquare() {
    Charis::Initialize(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello Square!");
    Charis::Utility::SetWindowBackground({ 0.4f, 0.4f, 0.5f });
    Charis::Utility::SetCursorBehavior(Charis::Utility::LockAndHide);

    struct VertexAttributes {
        glm::vec3 ver;
        glm::vec3 rgb;
        glm::vec2 tex;
    };
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
    auto squareToWorld = glm::mat4(1.0f);
    squareToWorld = glm::translate(squareToWorld, { 0.0f, 0.0f, -5.0f });

    const auto shader = Charis::Shader("Shaders/shader.vert", "Shaders/shader.frag");
    const auto container = Charis::Texture("Images/container2.png");
    const auto textureBinding = 0;
    shader.SetTexture("tex", textureBinding);
    container.BindTo(textureBinding);

    auto camera = Camera();

    while (Charis::WindowIsOpen()) { RunFrame([&](float dt) {

        if (Charis::Input::KeyState(Charis::Input::Escape, Charis::Input::Pressed))
            Charis::Utility::CloseWindow();

        ProcessInput(camera, dt);

        shader.SetMat4("model", squareToWorld);
        shader.SetMat4("view", camera.GetViewMatrix());
        shader.SetMat4("projection", glm::perspective(glm::radians(camera.Zoom), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f));

        shader.Draw(square);

    }); }

    Charis::CleanUp();
}

int main()
{

    HelloCameraSquare();

    return 0;
}
