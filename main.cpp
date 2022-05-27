// HelloWorld.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <cmath>
#include <GLAD/glad/glad.h>
#include <glfw-3.3.7/include/GLFW/glfw3.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include "libraries/stb_image.h"

#include "Input.h"
#include "Color.h"
#include "ShaderProgram.h"
#include "Texture.h"

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
	ShaderProgram shader = ShaderProgram::ShaderProgram("shaders/rainbowVertex.glsl", "shaders/rainbowFrag.glsl");

	// rect in NDC
	float rect[] = {
		// positions		// colors			// tex coords
		 0.5f,  0.5f, 0.0f,	1.0f, 0.0f, 0.0f,	1.0f, 1.0f,		// top right
		 0.5f, -0.5f, 0.0f,	0.0f, 1.0f, 0.0f,	1.0f, 0.0f,		// bottom right
		-0.5f, -0.5f, 0.0f,	0.0f, 0.0f, 1.0f,	0.0f, 0.0f,		// bottom left
		-0.5f,  0.5f, 0.0f,	1.0f, 1.0f, 0.0f,	0.0f, 1.0f		// top left 
	};
	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	// bind vertices & indices
	unsigned int VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(rect), rect, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	// position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// tex coords
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// bind textures
	Texture tex1 = Texture::Texture(0, "textures/container.jpg", false);
	tex1.loadTexture();

	Texture tex2 = Texture::Texture(1, "textures/awesomeFace.png", true);
	tex2.loadTexture();

	shader.useProgram();
	shader.setGlobalIntValue(0, "texture1");
	shader.setGlobalIntValue(1, "texture2");

	// render loop
	// TODO: double buffering
	while (!glfwWindowShouldClose(window))
	{
		Input::processInput(window);

		Color gray = Color::grayMid;
		glClearColor(gray.r, gray.g, gray.b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		// define texture and shader
		tex1.bindTexture();
		tex2.bindTexture();

		// create transformation matrix
		float t = (float)glfwGetTime();
		glm::mat4 trans = glm::mat4(1.0f);
		trans = glm::rotate(trans, t, glm::vec3(0.0, 0.0, 1.0));
		trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
		//trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));

		// bind transformation matrix
		shader.setGlobalMatrix4Value(trans, "transform");
		
		// draw object
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// create transformation matrix
		glm::mat4 trans2 = glm::mat4(1.0f);
		//trans2 = glm::rotate(trans2, (float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));
		trans2 = glm::translate(trans2, glm::vec3(-0.5f, 0.5f, 0.0f));
		float sint = static_cast<float>(std::sin(t));
		trans2 = glm::scale(trans2, glm::vec3(sint, sint, sint));

		// bind transformation matrix
		shader.setGlobalMatrix4Value(trans2, "transform");

		// draw object
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// draw window
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// de-allocate all resources
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	shader.deallocateProgram();

	// clean up GLFW resources
	glfwTerminate();
	return 0;
}