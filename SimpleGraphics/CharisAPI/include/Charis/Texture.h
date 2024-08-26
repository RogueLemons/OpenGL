#pragma once
#include <string>

namespace Charis {

	/// <summary>
	/// A texture is a 2D image that can be used in shaders.
	/// To use it in a shader it must first be bound to one of 32 global state textures, and then give the shader the global state. 
	/// </summary>
	class Texture
	{
	public:
		/// <summary>Constructor for a texture.</summary>
		/// <param name="pathToImage">File path to image to load into texture.</param>
		Texture(const std::string& pathToImage);
		/// <summary>Constructor for a texture. By adding a texture binding to the constructor the image is loaded as a texture and immedeately bound to the given global state.</summary>
		/// <param name="pathToImage">File path to image to load into texture. The global state binding index that should be used to access this texture.</param>
		/// <param name="binding">Value must be in [0, 31] range.</param>
		Texture(const std::string& pathToImage, unsigned int binding);
		~Texture();

		/// <summary>
		/// This function binds the texture to one of the 32 global texture states. Shaders access textures from the global states so this is a requirement for shaders.
		/// </summary>
		/// <param name="binding">Value must be in [0, 31] range. The global state binding index that should be used to access this texture.</param>
		void BindTo(unsigned int binding);
	private:
		unsigned int m_ID;
	};
}
