#include "Utility.h"
#include "Private/CharisGlobals.hpp"
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

		WindowDimensions GetWindowDimensions()
		{
			return { PrivateGlobal::Window::Width, PrivateGlobal::Window::Height };
		}

		void CloseWindow()
		{
			glfwSetWindowShouldClose(PrivateGlobal::Window, true);
		}

		void SetWindowBackground(const std::array<float, 3>& RGB)
		{
			PrivateGlobal::BackgroundRGB = RGB;
		}

		float GetTime()
		{
			return static_cast<float>(glfwGetTime());
		}

	}

	namespace Input {

		Position CursorPosition()
		{
			return { PrivateGlobal::Mouse::X, PrivateGlobal::Mouse::Y };
		}

		float MouseWheel()
		{
			return PrivateGlobal::Mouse::Wheel;
		}

		bool KeyState(Key key, Trigger trigger)
		{
			return glfwGetKey(PrivateGlobal::Window, key) == trigger;
		}

		bool MouseButtonState(Mouse button, Trigger trigger)
		{
			return glfwGetMouseButton(PrivateGlobal::Window, button) == trigger;
		}

	}

}

