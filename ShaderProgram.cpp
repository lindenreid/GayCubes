#include <iostream>
#include <GLAD/glad/glad.h>
#include <glfw-3.3.7/include/GLFW/glfw3.h>

#include "ShaderProgram.h"

namespace GayCubes
{
	ShaderProgram::ShaderProgram(const char* vertexPath, const char* fragmentPath)
	{
		// retrieve code from file path
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		// ensure ifstream objs can throw exceptions
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			// open files
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;
			// read file buffer into streams
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			// close file handlers
			vShaderFile.close();
			fShaderFile.close();
			// convert stream into string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR: shader file not successfully read" << std::endl;
		}
		const char* vertShaderSource = vertexCode.c_str();
		const char* fragShaderSource = fragmentCode.c_str();

		unsigned int vertexShader;
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		createShader(vertexShader, vertShaderSource);

		unsigned int fragmentShader;
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		createShader(fragmentShader, fragShaderSource);

		shaderID = glCreateProgram();

		glAttachShader(shaderID, vertexShader);
		glAttachShader(shaderID, fragmentShader);
		
		glLinkProgram(shaderID);

		int success;
		char infoLog[512];
		glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shaderID, 512, NULL, infoLog);
			std::cout << "ERROR: shader program creation failed\n" << infoLog << std::endl;
		}

		// remove shaders once we've linked them
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	void ShaderProgram::createShader(unsigned int shader, const char* source)
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

	void ShaderProgram::useProgram()
	{
		glUseProgram(shaderID);
	}

	void ShaderProgram::deallocateProgram()
	{
		glDeleteProgram(shaderID);
	}

	// note: requires you call glUseProgram on this shader first
	void ShaderProgram::setGlobalVec4Value(float value[], const char name[])
	{
		int valRef = glGetUniformLocation(shaderID, name);
		glUniform4f(valRef, value[0], value[1], value[2], value[3]);
	}

	// note: requires you call glUseProgram on this shader first
	void ShaderProgram::setGlobalFloatValue(float value, const char name[])
	{
		int valRef = glGetUniformLocation(shaderID, name);
		glUniform1f(valRef, value);
	}

	// note: requires you call glUseProgram on this shader first
	void ShaderProgram::setGlobalBoolValue(bool value, const char name[])
	{
		int valRef = glGetUniformLocation(shaderID, name);
		glUniform1i(valRef, (int)value);
	}

	// note: requires you call glUseProgram on this shader first
	void ShaderProgram::setGlobalIntValue(int value, const char name[])
	{
		int valRef = glGetUniformLocation(shaderID, name);
		glUniform1i(valRef, value);
	}
}