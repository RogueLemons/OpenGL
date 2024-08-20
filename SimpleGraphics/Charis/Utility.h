#pragma once
#include <string>
#include <array>

#define VAL const auto
#define VAR auto
#define REF auto&
#define SCN const auto&

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

		// Closes the window.
		void CloseWindow();

		/// <summary>Sets the background color of the window.</summary>
		/// <param name="RGB">RGB color values ranging from 0.0 to 1.0.</param>
		void SetWindowBackground(const std::array<float, 3>& RGB);
	}

}