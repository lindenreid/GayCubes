// HelloWorld.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
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

	// VAO
	unsigned int VAO;
 	glGenVertexArrays(1, &VAO);

	// VBO
	unsigned int VBO; // OpenGL references objects by ID 
	glGenBuffers(1, &VBO); // generate an ID for our mesh

	// centered triangle in NDC
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

	// one-time VAO initialization 
	// 1. bind vertex array
	glBindVertexArray(VAO);
	// 2. copy our verts into a buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // set buffer target to VBO as an array buffer (the type used for meshes)
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // send to 
	// 3. link vertex attributes
	// location = 0 (vertex position input in vertex input)
	// size = 3 (# of values)
	// data type = FLOAT
	// normalized = false
	// stride = size of data entries (3*float because we have 3 floats describing xyz position)
	// offset = 0 (position where data begins)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// render loop
	// TODO: double buffering
	while (!glfwWindowShouldClose(window))
	{
		Input::processInput(window);

		Color gray = Color::grayMid;
		glClearColor(gray.r, gray.g, gray.b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// 4. draw object
		glUseProgram(shader.shaderProgram);
		glBindVertexArray(VAO);
		// primitive type: triangles
		// starting index of vertex array: 0
		// how many verts: 3
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