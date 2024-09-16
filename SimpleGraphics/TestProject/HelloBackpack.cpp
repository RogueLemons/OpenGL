#include "HelloBackpack.h"
#include <functional>

// Charis
#include "Charis/Initialize.h"
#include "Charis/Utility.h"
#include "Charis/Shader.h"
#include "Charis/Model.h"
#include "Charis/Camera.h"

// Libraries
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

// Functions
namespace {

    // Holds a REFERENCE to a model, as well as a position, rotation, and scale.
    // A model should be seen as a blueprint while this is the actual object.
    struct WorldObject {
        WorldObject(const Charis::Model& model, glm::mat4 position = { 1.0f }, glm::mat4 rotation = { 1.0f }, float scale = { 1.0f })
            : model(model), position(position), rotation(rotation), scale(scale)
        {}

        const Charis::Model& model;
        glm::mat4 position;
        glm::mat4 rotation;
        float scale;

        glm::mat4 ModelToWorldMatrix() const { return position * rotation * glm::scale({ 1.0f }, glm::vec3(scale)); }
        void DrawWith(Charis::Shader shader) const {
            shader.SetMat4("model", ModelToWorldMatrix());
            shader.Draw(model);
        }
    };

    // Helper function to clean to make engine loop code easier to read
    void RunFrame(const std::function<void(float dt)>& frameFunction) {
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
            camera.ProcessRotation(deltaX, -deltaY);
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
    // Manages mouse and keyboard input
    void ProcessInput(Charis::Camera& camera, float deltaTime) {
        using namespace ProcessInputHelperFunctions;

        Keyboard(camera, deltaTime);
        MousePosition(camera);
        MouseScroll(camera);
    }

}

void HelloBackpack() {
    // Set up Charis
    Charis::Initialize(800, 600, "Hello Backpack!");
    Charis::Utility::SetWindowBackground({ 0.4f, 0.4f, 0.5f });
    Charis::Utility::SetCursorBehavior(Charis::Utility::LockAndHide);

    // Load and set up backpack model
    const auto backpackModel = Charis::Model("Models/backpack/backpack.obj");
    const auto backpackStartPosition = glm::translate(glm::mat4(1.0f), { 0.0f, 0.0f, -5.0f });
    auto backpack = WorldObject(backpackModel, backpackStartPosition, glm::mat4(1.0f), 0.5f);

    // Load and set up shaders
    const auto shader = Charis::Shader("Shaders/hello_backpack.vert", "Shaders/hello_backpack.frag", Charis::Shader::Filepath, 1);
    shader.SetVec3("dirLight.direction", { 1.0f, 1.0f, 0.0f });
    const auto whiteLight = glm::vec3(1.0f, 1.0f, 1.0f);
    shader.SetVec3("dirLight.ambient", 0.4f * whiteLight);
    shader.SetVec3("dirLight.diffuse", 0.7f * whiteLight);
    shader.SetVec3("dirLight.specular", 0.7f * whiteLight);

    // Create a camera
    auto camera = Charis::Camera();

    // Run engine loop
    while (Charis::WindowIsOpen()) { RunFrame([&](float dt) {

        ProcessInput(camera, dt);

        shader.SetMat4("view", camera.ViewMatrix());
        shader.SetMat4("projection", camera.ProjectionMatrix());

        backpack.rotation = glm::rotate(backpack.rotation, 0.001f, glm::normalize(glm::vec3{ 0.0f, 1.0f, 0.0f }));
        backpack.position = glm::translate(backpackStartPosition, glm::vec3(0.0f, 0.2 * glm::cos(Charis::Utility::GetTime() * 2.0f), 0.0f));
        backpack.DrawWith(shader);

    }); }

    // End background processes before closing
    Charis::CleanUp();
}