#include <iostream>
#include "Charis/Initialize.h"
#include "Charis/Utility.h"


int main()
{
    Charis::Initialize();

    while (Charis::WindowIsOpen()) {
        Charis::InitializeLoop();
        if (Charis::Input::KeyState(Charis::Input::Key::Escape, Charis::Input::Pressed))
            Charis::Utility::CloseWindow();
        
        if (Charis::Input::KeyState(Charis::Input::Key::W, Charis::Input::Pressed)) {
            std::cout << "W" << std::endl;
        }
    }

    Charis::CleanUp();
   
    return 0;
}