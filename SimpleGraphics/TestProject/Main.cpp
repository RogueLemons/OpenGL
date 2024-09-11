#include <iostream>
#include <vector>
#include <functional>
#include <numeric>

// Charis
#include "Charis/Initialize.h"
#include "Charis/Utility.h"
#include "Charis/Shader.h"
#include "Charis/Model.h"
#include "Charis/Camera.h"

// Libraries
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

// Settings
constexpr unsigned int SCREEN_WIDTH = 800;
constexpr unsigned int SCREEN_HEIGHT = 600;

// Functions
static void RunFrame(const std::function<void(float dt)>& frameFunction) {
    // Static
    static float lastTime = Charis::Utility::GetTime();
    
    // Run frame
    Charis::StartFrame();

    const auto time = Charis::Utility::GetTime();
    const auto deltaTime = time - lastTime;
    lastTime = time;

    frameFunction(deltaTime);
    Charis::EndFrame();
}

namespace ProcessInputHelperFunctions {
    static void Keyboard(Charis::Camera& camera, float deltaTime) {
        using namespace Charis::Input;

        // Close window
        if (KeyState(Key::Escape, Trigger::Pressed))
            Charis::Utility::CloseWindow();

        // Move camera
        Charis::Camera::Movement direction 
        {
            .forward  = KeyState(Key::W, Pressed),
            .backward = KeyState(Key::S, Pressed),
            .right    = KeyState(Key::D, Pressed),
            .left     = KeyState(Key::A, Pressed),
            .up       = KeyState(Key::Space, Pressed),
            .down     = KeyState(Key::LeftControl, Pressed)
        };
        camera.ProcessMovement(direction, deltaTime);
    }
    static void MousePosition(Charis::Camera& camera) {
        // Statics
        static bool cursorIsUnknown = true;
        static auto lastCursor = Charis::Input::CursorPosition();

        // CursorPosition gives {0, 0} until first time it is moved
        if (cursorIsUnknown) {
            lastCursor = Charis::Input::CursorPosition();

            if (lastCursor.X == 0.0f && lastCursor.Y == 0.0f) return;
            else cursorIsUnknown = false;
        }

        // Cursor delta
        const auto cursor = Charis::Input::CursorPosition();
        const auto deltaX = cursor.X - lastCursor.X;
        const auto deltaY = cursor.Y - lastCursor.Y;
        camera.ProcessDirection(deltaX, -deltaY);
        lastCursor = cursor;
    }
    static void MouseScroll(Charis::Camera& camera) {
        static auto lastWheel = Charis::Input::MouseWheel();

        const auto wheel = Charis::Input::MouseWheel();
        const auto deltaWheel = wheel - lastWheel;
        camera.ProcessZoom(deltaWheel);
        lastWheel = wheel;
    }
}
static void ProcessInput(Charis::Camera& camera, float deltaTime) {
    using namespace ProcessInputHelperFunctions;

    Keyboard(camera, deltaTime);
    MousePosition(camera);
    MouseScroll(camera);
}

static void HelloBackpack() {
    Charis::Initialize(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello Backpack!");
    Charis::Utility::SetWindowBackground({ 0.4f, 0.4f, 0.5f });
    Charis::Utility::SetCursorBehavior(Charis::Utility::LockAndHide);

    const auto backpack = Charis::Model("Models/backpack/backpack.obj");
    auto backpackToWorld = glm::mat4(1.0f);
    backpackToWorld = glm::translate(backpackToWorld, { 0.0f, 0.0f, -5.0f });

    const auto shader = Charis::Shader("Shaders/shader.vert", "Shaders/shader.frag", Charis::Shader::Filepath, 1);
    auto camera = Charis::Camera();

    // Run engine loop
    while (Charis::WindowIsOpen()) { RunFrame([&](float dt) {

        ProcessInput(camera, dt);

        shader.SetMat4("model", backpackToWorld);
        shader.SetMat4("view", camera.ViewMatrix());
        shader.SetMat4("projection", camera.ProjectionMatrix());

        shader.Draw(backpack);

    }); }

    Charis::CleanUp();
}

int main()
{

    HelloBackpack();

    return 0;
}
