#pragma once
#include <string>
#include <array>

namespace Charis {

	namespace Helper {

		/// <summary>Asserts that a condition is true at runtime and aborts the program if it is not.</summary>
		/// <param name="condition">Condition that must be true for program to keep running.</param>
		/// <param name="errorMessage">Error message that is printed if condition is false.</param>
		void RuntimeAssert(bool condition, const std::string& errorMessage);

	}

	namespace Utility {

		// Used for SetCursorBehavior function.
		enum CursorBehavior {
			// Normal and default behavior. Can move freely inside and outside of window.
			Normal,
			// Cursor is locked to window and invisible.
			LockAndHide
		};
		// Sets how the cursor should be managed by the window.
		void SetCursorBehavior(CursorBehavior behavior);

		struct WindowDimensions { unsigned int Width; unsigned int Height; };
		// Get window dimensions
		WindowDimensions GetWindowDimensions();

		// Closes the window.
		void CloseWindow();

		/// <summary>Sets the background color of the window.</summary>
		/// <param name="RGB">RGB color values ranging from 0.0 to 1.0.</param>
		void SetWindowBackground(const std::array<float, 3>& RGB);

		/// <summary>Returns the time in seconds since initialization.</summary>
		float GetTime();
	}

	namespace Input {

		struct Position {
			float X{};
			float Y{};
		};
		// Gets the X and Y coordinates of the cursor.
		Position CursorPosition();
		// Gets the position of the mouse wheel.
		float MouseWheel();

		// Must match GLFW implementation
		enum Trigger {
			Released = 0,
			Pressed = 1,
		};
		// Must match GLFW implementation
		enum Key {
			KB_0 = 48,
			KB_1 = 49,
			KB_2 = 50,
			KB_3 = 51,
			KB_4 = 52,
			KB_5 = 53,
			KB_6 = 54,
			KB_7 = 55,
			KB_8 = 56,
			KB_9 = 57,
			A = 65,
			B = 66,
			C = 67,
			D = 68,
			E = 69,
			F = 70,
			G = 71,
			H = 72,
			I = 73,
			J = 74,
			K = 75,
			L = 76,
			M = 77,
			N = 78,
			O = 79,
			P = 80,
			Q = 81,
			R = 82,
			S = 83,
			T = 84,
			U = 85,
			V = 86,
			W = 87,
			X = 88,
			Y = 89,
			Z = 90,
			Space = 32,
			Escape = 256,
			Enter = 257,
			Tab = 258,
			Backspace = 259,
			ArrowRight = 262,
			ArrowLeft = 263,
			ArrowDown = 264,
			ArrowUp = 265,
			LeftShift = 340,
			LeftControl = 341
		};
		// Must match GLFW implementation
		enum Mouse {
			MB_1 = 0,
			MB_2 = 1,
			MB_3 = 2,
			MB_4 = 3,
			MB_5 = 4,
			MB_6 = 5,
			MB_7 = 6,
			MB_8 = 7,
		};

		bool KeyState(Key key, Trigger trigger);

		bool MouseButtonState(Mouse button, Trigger trigger);
	}

}