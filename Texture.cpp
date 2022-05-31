#include <iostream>
#include <GLAD/glad/glad.h>
#include <glfw-3.3.7/include/GLFW/glfw3.h>
#include "libraries/stb_image.h";

#include "Texture.h"

namespace GayCubes
{
	Texture::Texture(int targetIndex, const char* textureFilePath, bool alpha)
	{
		_textureFilePath = textureFilePath;
		_texture = 0;
		_targetIndex = targetIndex;
		_alpha = alpha;
	}

	void Texture::loadTexture()
	{
		// bind texture
		glGenTextures(1, &_texture);
		
		switch (_targetIndex)
		{
		case 0: glActiveTexture(GL_TEXTURE0); break;
		case 1: glActiveTexture(GL_TEXTURE1); break;
		}

		glBindTexture(GL_TEXTURE_2D, _texture);
		// set tex params
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		// load texture
		int w, h, nrChannels;
		unsigned char* data = stbi_load(_textureFilePath, &w, &h, &nrChannels, 0);
		if (data)
		{
			if (_alpha)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			}
			else
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			}
			glGenerateMipmap(GL_TEXTURE_2D);
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