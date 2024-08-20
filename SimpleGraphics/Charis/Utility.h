#pragma once
#include <string>

#define VAL const auto
#define VAR auto
#define REF auto&
#define SCN const auto&

namespace Charis {

	namespace Helper {

		void RuntimeAssert(bool condition, const std::string& errorMessage);

	}

	namespace Utility {

		enum CursorBehavior {
			// Normal and default behavior. Can move freely inside and outside of window.
			Normal,
			// Cursor is locked to window and invisible.
			LockAndHide
		};
		// Sets how the cursor should be managed by the window.
		void SetCursorBehavior(CursorBehavior behavior);

	}

}