#include <iostream>
#include <vector>

// Charis
#include "Charis/Initialize.h"
#include "Charis/Utility.h"
#include "Charis/Model.h"
#include "Charis/Shader.h"


int main()
{
    Charis::Initialize();

    const std::vector<float> vertices = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f
    };
    const auto triangle = Charis::Model(vertices, {3});

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


    while (Charis::WindowIsOpen()) {
        Charis::InitializeLoop();
        if (Charis::Input::KeyState(Charis::Input::Escape, Charis::Input::Pressed))
            Charis::Utility::CloseWindow();

        shader.Draw(triangle);
        
        if (Charis::Input::KeyState(Charis::Input::W, Charis::Input::Pressed)) {
            std::cout << "W" << std::endl;
        }
    }

    Charis::CleanUp();
   
    return 0;
}