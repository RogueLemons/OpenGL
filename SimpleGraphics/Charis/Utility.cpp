#include "Utility.h"
#include "Private.hpp"
#include <iostream>
#include <stdlib.h>

// Libraries
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Charis {

	namespace Helper {

		void RuntimeAssert(bool condition, const std::string& errorMessage)
		{
			if (!condition) {
				std::cout << errorMessage << std::endl;
				abort();
			}
		}

	}

	namespace Utility {

		void SetCursorBehavior(CursorBehavior behavior)
		{
			switch (behavior) {
			case CursorBehavior::Normal:
				glfwSetInputMode(PrivateGlobal::Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				break;
			case CursorBehavior::LockAndHide:
				glfwSetInputMode(PrivateGlobal::Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				break;
			}
		}

		Position CursorPosition()
		{
			return { PrivateGlobal::Mouse::X, PrivateGlobal::Mouse::Y };
		}

		float MouseWheel()
		{
			return PrivateGlobal::Mouse::Wheel;
		}

		void CloseWindow()
		{
			glfwSetWindowShouldClose(PrivateGlobal::Window, true);
		}

		void SetWindowBackground(const std::array<float, 3>& RGB)
		{
			PrivateGlobal::BackgroundRGB = RGB;
		}

	}

}

