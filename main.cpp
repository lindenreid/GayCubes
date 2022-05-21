// HelloWorld.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <GLAD/glad/glad.h>
#include <glfw-3.3.7/include/GLFW/glfw3.h>

#include "Input.h"
#include "Color.h"

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

	// render loop
	// TODO: double buffering
	while (!glfwWindowShouldClose(window))
	{
		Input::processInput(window);

		Color gray = Color::grayMid;
		glClearColor(gray.r, gray.g, gray.b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// clean up GLFW resources
	glfwTerminate();
	return 0;
}