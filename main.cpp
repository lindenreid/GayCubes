// HelloWorld.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <GLAD/glad/glad.h>
#include <glfw-3.3.7/include/GLFW/glfw3.h>

#include "Input.h"
#include "Color.h"

using namespace GayCubes;

// sin
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

// SIIIIN
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); \n"
"}\0";

void CreateShader(unsigned int shader, const char* source)
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

void CreateShaderProgram(unsigned int shaderProgram, unsigned int vertexShader, unsigned int fragmentShader)
{
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
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, false);

	GLFWwindow* window = glfwCreateWindow(800, 600, "GayCubes", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window." << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// GLAD manages function pointers for OpenGL
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialized GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);

	// render loop
	// TODO: double buffering
	while (!glfwWindowShouldClose(window))
	{
		Input::processInput(window);

		Color gray = Color::grayMid;
		glClearColor(gray.r, gray.g, gray.b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// centered triangle in NDC
		float vertices[] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
		};

		unsigned int VBO; // OpenGL references objects by ID 
		glGenBuffers(1, &VBO); // generate an ID for our mesh
		glBindBuffer(GL_ARRAY_BUFFER, VBO); // set buffer target to VBO as an array buffer (the type used for meshes)
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // send to GPU

		// create the shaders
		unsigned int vertexShader;
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		CreateShader(vertexShader, vertexShaderSource);

		unsigned int fragmentShader;
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		CreateShader(fragmentShader, fragmentShaderSource);

		unsigned int shaderProgram;
		shaderProgram = glCreateProgram();
		CreateShaderProgram(shaderProgram, vertexShader, fragmentShader);

		glUseProgram(shaderProgram);

		// remove shaders once we've linked them
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		// draw window
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// clean up GLFW resources
	glfwTerminate();
	return 0;
}