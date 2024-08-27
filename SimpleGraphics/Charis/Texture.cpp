#include "Texture.h"
#include "Utility.h"
#include "Private/stb_image.h"
#include <array>

// Libraries
#include <glad/glad.h>

namespace Charis {

	Texture::Texture(const std::string& pathToImage)
	{
        glGenTextures(1, &m_ID);
        glBindTexture(GL_TEXTURE_2D, m_ID);

        // set the texture wrapping parameters, (GL_REPEAT is default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // tell stb_image.h to flip loaded texture's on the y-axis, consider moving to Charis initialization
        stbi_set_flip_vertically_on_load(true);

        // load image, create texture and generate mipmaps
        int width, height, nrChannels;
        const int desiredNrChannels = 4;
        unsigned char* data = stbi_load(pathToImage.data(), &width, &height, &nrChannels, desiredNrChannels);
        Helper::RuntimeAssert(data, "Failed to load texture: " + pathToImage);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_ID);
	}

    void Texture::BindTo(unsigned int binding) const
    {
        Helper::RuntimeAssert(31 >= binding && binding >= 0, "Texture global state binding index must be in the range [0, 31].");
        int bindingCode = binding + GL_TEXTURE0; // 0x84C0
        glActiveTexture(bindingCode);
        glBindTexture(GL_TEXTURE_2D, m_ID);
    }

}


