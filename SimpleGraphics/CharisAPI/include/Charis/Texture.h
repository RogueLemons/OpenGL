#pragma once
#include <string>
#include <memory>
#include <array>

namespace Charis {

	/// <summary>
	/// A texture is a 2D image that can be used in shaders.
	/// To use it in a shader it must first be bound to one of 32 global state textures, and then give the shader the global state. 
	/// </summary>
	class Texture
	{
	public:
		enum TextureType {
			Diffuse = 0,
			Specular = 1,
			Normal = 2,
			Height = 3,
			Ambient = 4,
			Null
		};
		static constexpr std::array<const char*, Null> ShaderTextureNames { 
			"DiffuseTexture_", 
			"SpecularTexture_", 
			"NormalTexture_", 
			"HeightTexture_", 
			"AmbientTexture_" 
		};
		TextureType Type;

		/// <summary>Constructor for a texture.</summary>
		/// <param name="pathToImage">File path to image to load into texture.</param>
		/// <param name="type">Type of texture it is. Null textures require manual handling and will not be automatically added to shaders when drawing model components.</param>
		Texture(const std::string& pathToImage, TextureType type = Null);
		~Texture();

		/// <summary>
		/// This function binds the texture to one of the 32 global texture states. Shaders access textures from the global states so this is a requirement for shaders.
		/// </summary>
		/// <param name="binding">Value must be in [0, 31] range. The global state binding index that should be used to access this texture.</param>
		void BindTo(unsigned int binding) const;

	private:
		struct TextureMember {
			unsigned int ID{};
		};
		std::shared_ptr<TextureMember> m = std::make_shared<TextureMember>();
	};
}
