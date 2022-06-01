#ifndef _TEXTURE_OBJ
#define _TEXTURE_OBJ

#include <GLAD/glad/glad.h>

namespace GayCubes
{
	class Texture
	{
	public:
		Texture(int targetIndex, const char* textureFilePath, bool flip);
		void loadTexture();
		void bindTexture();

	private:
		const char* _textureFilePath;
		unsigned int _texture;
		unsigned int _targetIndex;

		bool _openGLflip;
	};
}

#endif //_TEXTURE_OBJ

