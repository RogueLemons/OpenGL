#pragma once
#include <string>

namespace Charis {

	/// <summary>
	/// Performs all background work necessary to start using Charis. Don't forget to call the CleanUp function before closing the program.
	/// </summary>
	/// <param name="width">Width of window in pixels.</param>
	/// <param name="height">Height of window in pixels.</param>
	/// <param name="name">Name of the application and window header.</param>
	void Initialize(unsigned int width = 800, unsigned int height = 600, const std::string& name = "Charis Engine Application");

	/// <summary>Performs necessary background work for frame to start. Do not forget to also end the frame. </summary>
	void StartFrame();

	/// <summary>Ends the frame. </summary>
	void EndFrame();

	/// <summary>Checks if the window should be open or is closed. Use this as the condition for the while loop of the engine.</summary>
	/// <returns>True if the window should be open.</returns>
	bool WindowIsOpen();

	/// <summary>Clears up background processes. Call this function before exiting program.</summary>
	void CleanUp();
}