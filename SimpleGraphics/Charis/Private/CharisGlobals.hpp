#pragma once
#include <array>

// Libraries
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Charis {

	namespace PrivateGlobal {

		inline GLFWwindow* Window = nullptr;
		struct Window {
			inline static unsigned int Width{};
			inline static unsigned int Height{};
		};

		inline std::array<float, 3> BackgroundRGB{};

		struct Mouse {
			inline static float X{};
			inline static float Y{};
			inline static float Wheel{};
		};


	}

}