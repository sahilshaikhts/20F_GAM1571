#include "FrameworkPCH.h"
#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include"../../Libraries/stb/stb_image.h"

namespace fw {
	Texture::Texture(const char* fName) {
		int width, height, numComponents;

		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(fName, &width, &height, &numComponents, 4);
		if (data != nullptr)
		{
			int bp = 1;
			glGenTextures(1, &m_TextureHandle);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, m_TextureHandle);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE,data);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

			glBindTexture(GL_TEXTURE_2D, 0);
		}
		stbi_image_free(data);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1,&m_TextureHandle);
	}

}
