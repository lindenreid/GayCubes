// HelloWorld.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <cmath>
#include <GLAD/glad/glad.h>
#include <glfw-3.3.7/include/GLFW/glfw3.h>

#include "Input.h"
#include "Color.h"
#include "ShaderProgram.h"

using namespace GayCubes;

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

	// shader program
	ShaderProgram shader = ShaderProgram::ShaderProgram();

	// triangle in NDC
	float tri1[] = {
		// pos				// colors
		0.2f, 0.8f, 0.0f,	1.0f, 0.0f, 0.0f,
		0.8f, 0.0f, 0.0f,	0.0f, 1.0f, 0.0f,
		0.2f, 0.0f, 0.0f,	0.0f, 0.0f, 1.0f
	};

	// vertex array objects
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	// vertex buffer object
	unsigned int VBO; // OpenGL references objects by ID 
	glGenBuffers(1, &VBO); // generate an ID for our mesh

	// one-time VAO initialization 
	// 1. bind vertex array
	glBindVertexArray(VAO);
	// 2. bind vbo
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // set buffer target to VBO as an array buffer (the type used for meshes)
	glBufferData(GL_ARRAY_BUFFER, sizeof(tri1), tri1, GL_STATIC_DRAW); // send to gpu
	// 4. link vertex attributes
	// position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// render loop
	// TODO: double buffering
	while (!glfwWindowShouldClose(window))
	{
		Input::processInput(window);

		Color gray = Color::grayMid;
		glClearColor(gray.r, gray.g, gray.b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// set uniform (global) shader value to change color with time
		float t = glfwGetTime();
		float greenVal = (sin(t) / 2.0f) + 0.5f;
		
		glUseProgram(shader.shaderProgram);
		shader.SetGlobalValue(greenVal, "globalColor");
		
		// draw object
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// draw window
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// de-allocate all resources
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shader.shaderProgram);

	// clean up GLFW resources
	glfwTerminate();
	return 0;
}