#include "Texture.h"
#include "Utility.h"
#include "Core/stb_image.h"
#include <array>

// Libraries
#include <glad/glad.h>

namespace Charis {

	Texture::Texture(const std::string& pathToImage)
	{
        glGenTextures(1, &m_ID);
        glBindTexture(GL_TEXTURE_2D, m_ID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	                // set the texture wrapping parameters, (GL_REPEAT is default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_set_flip_vertically_on_load(true);     // tell stb_image.h to flip loaded texture's on the y-axis, consider moving to Charis initialization
        int width, height, nrChannels;              // load image, create texture and generate mipmaps
        unsigned char* data = stbi_load("images/container.jpg", &width, &height, &nrChannels, 0);
        Helper::RuntimeAssert(data, "Failed to load texture: " + pathToImage);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
	}

    Texture::Texture(const std::string& pathToImage, unsigned int binding)
        : Texture(pathToImage)
    {
        BindTo(binding);
    }

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_ID);
	}

    void Texture::BindTo(unsigned int binding)
    {
        Helper::RuntimeAssert(31 >= binding && binding >= 0, "Texture global state binding index must be in the range [0, 31].");
        constexpr std::array<int, 32> bindingCodes = {
            0x84C0,
            0x84C1,
            0x84C2,
            0x84C3,
            0x84C4,
            0x84C5,
            0x84C6,
            0x84C7,
            0x84C8,
            0x84C9,
            0x84CA,
            0x84CB,
            0x84CC,
            0x84CD,
            0x84CE,
            0x84CF,
            0x84D0,
            0x84D1,
            0x84D2,
            0x84D3,
            0x84D4,
            0x84D5,
            0x84D6,
            0x84D7,
            0x84D8,
            0x84D9,
            0x84DA,
            0x84DB,
            0x84DC,
            0x84DD,
            0x84DE,
            0x84DF
        };
        glActiveTexture(bindingCodes.at(binding));
        glBindTexture(GL_TEXTURE_2D, m_ID);
    }

}


