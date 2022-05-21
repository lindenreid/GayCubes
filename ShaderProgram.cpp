#include <iostream>
#include <GLAD/glad/glad.h>
#include <glfw-3.3.7/include/GLFW/glfw3.h>

#include "ShaderProgram.h"

namespace GayCubes
{
	ShaderProgram::ShaderProgram()
	{
		shaderProgram = glCreateProgram();

		unsigned int vertexShader;
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		CreateShader(vertexShader, vertexShaderSource);

		unsigned int fragmentShader;
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		CreateShader(fragmentShader, fragmentShaderSource);

		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		
		glLinkProgram(shaderProgram);

		int success;
		char infoLog[512];
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			std::cout << "ERROR: shader program creation failed\n" << infoLog << std::endl;
		}

		// remove shaders once we've linked them
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	void ShaderProgram::CreateShader(unsigned int shader, const char* source)
	{
		glShaderSource(shader, 1, &source, NULL);
		glCompileShader(shader);

		// check for compile errors in shader
		int success;
		char infoLog[512];
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::cout << "ERROR: vertex shader compilation failed\n" << infoLog << std::endl;
		}
	}
}