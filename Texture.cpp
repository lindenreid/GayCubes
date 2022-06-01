#include <iostream>
#include <GLAD/glad/glad.h>
#include <glfw-3.3.7/include/GLFW/glfw3.h>
#include "libraries/stb_image.h"

#include "Texture.h"

namespace GayCubes
{
	Texture::Texture(int targetIndex, const char* textureFilePath, bool flip)
	{
		_textureFilePath = textureFilePath;
		_texture = 0;
		_targetIndex = targetIndex;
		_openGLflip = flip;

		loadTexture();
	}

	void Texture::loadTexture()
	{
		stbi_set_flip_vertically_on_load(_openGLflip);

		// bind texture
		glGenTextures(1, &_texture);
		
		// load texture
		int w, h, nrChannels;
		unsigned char* data = stbi_load(_textureFilePath, &w, &h, &nrChannels, 0);
		if (data)
		{
			GLenum format = GL_RED;
			switch (nrChannels)
			{
			case 1:
				format = GL_RED;
				break;
			case 2:
				format = GL_RG;
				break;
			case 3:
				format = GL_RGB;
				break;
			case 4:
				format = GL_RGBA;
				break;
			default:
				std::cout << "texture import type not defined for nrChannel count: " << nrChannels << std::endl;
				break;
			}

			glBindTexture(GL_TEXTURE_2D, _texture);
			glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
			
			// set tex params
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
		else {
			std::cout << "failed to load texture" << std::endl;
		}

		stbi_image_free(data);
	}

	void Texture::bindTexture()
	{
		switch (_targetIndex)
		{
		case 0: glActiveTexture(GL_TEXTURE0); break;
		case 1: glActiveTexture(GL_TEXTURE1); break;
		}
		glBindTexture(GL_TEXTURE_2D, _texture);
	}
}