#pragma once

namespace Charis {

	namespace Settings {

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