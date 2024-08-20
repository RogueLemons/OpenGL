#pragma once
#include <string>

namespace Charis {

	/// <summary>
	/// Performs all background work necessary to start using Charis.
	/// </summary>
	/// <param name="name">Name of the application and window header.</param>
	/// <param name="width">Width of window in pixels.</param>
	/// <param name="height">Height of window in pixels.</param>
	void Initialize(const std::string& name = "Charis Engine Application", unsigned int width = 800, unsigned int height = 600);

	/// <summary>Performs the necessary background work for each loop of the engine. </summary>
	void InitializeLoop();

	/// <summary>Checks if the window should be open or is closed. Use this as the condition for the while loop of the engine.</summary>
	/// <returns>True if the window should be open.</returns>
	bool WindowIsOpen();
}