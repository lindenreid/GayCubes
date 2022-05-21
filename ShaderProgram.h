#ifndef _SHADER_PROGRAM
#define _SHADER_PROGRAM

#include <GLAD/glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace GayCubes
{
	class ShaderProgram
	{
	public:
		// constructors
		ShaderProgram(const char* vertexPath, const char* fragmentPath);
		
		// general usage
		void useProgram();
		void deallocateProgram();
		
		// uniform value setters
		void setGlobalVec4Value(float value[], const char name[]);
		void setGlobalFloatValue(float value, const char name[]);
		void setGlobalBoolValue(bool value, const char name[]);
		void setGlobalIntValue(int value, const char name[]);

	private:
		unsigned int shaderID;

		void createShader(unsigned int shader, const char* source);
	};
}

#endif //_SHADER_PROGRAM

