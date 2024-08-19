#pragma once
#include <string>

namespace Charis {

	/// <summary>
	/// Performs all background work necessary to start using Charis.
	/// </summary>
	/// <param name="name">Name of the application and window header.</param>
	/// <param name="width">Width of window in pixels.</param>
	/// <param name="height">Height of window in pixels.</param>
	/// <returns>True if initialization is successfully completed.</returns>
	bool Initialize(const std::string& name = "Charis Engine Application", unsigned int width = 800, unsigned int height = 600);

}