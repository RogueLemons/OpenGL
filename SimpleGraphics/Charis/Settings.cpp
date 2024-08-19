#pragma once
#include "Settings.h"
#include "Private.hpp"

// Libraries
#include <GLFW/glfw3.h>

namespace Charis {

	namespace Settings {

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

	}

}