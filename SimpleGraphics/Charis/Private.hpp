#pragma once
#include <functional>

// Libraries
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Charis {

	namespace PrivateGlobal {

		inline GLFWwindow* Window = nullptr;

		struct Mouse {
			inline static float X{};
			inline static float Y{};
			inline static float Wheel{};
		};


	}

}