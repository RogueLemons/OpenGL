#pragma once

// Libraries
#include <GLFW/glfw3.h>

namespace Charis {

	namespace PrivateGlobal {

		GLFWwindow* Window;

		struct Mouse {
			static float X;
			static float Y;
			static float Wheel;
		};


	}

}