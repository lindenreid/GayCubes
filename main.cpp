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
#include "Camera.h"
#include "Time.h"

using namespace GayCubes;

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, false);

	int windowWidth = 800;
	int windowHeight = 600;

	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "GayCubes", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window." << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// set up input capture
	Input input = Input::Input(window);

	// GLAD manages function pointers for OpenGL
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialized GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, windowWidth, windowHeight);

	// enable depth buffer
	glEnable(GL_DEPTH_TEST);

	// shader program
	ShaderProgram shader = ShaderProgram::ShaderProgram("shaders/rainbowVertex.glsl", "shaders/rainbowFrag.glsl");
	ShaderProgram lightShader = ShaderProgram::ShaderProgram("shaders/lightVertex.glsl", "shaders/lightFrag.glsl");

	// camera
	Camera camera = Camera::Camera(
		glm::vec3(0.0f, 0.0f, 3.0f),	// position
		glm::vec3(0.0f, 1.0f, 0.0f)		// world up
	);

	// create perspective projection matrix
	glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);

	// time
	Time time = Time::Time();
	time.Initialize();

	// cube verts
	float cubeVerts[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f	
	};

	// setup cube VAO
	// -----------------------------
	unsigned int VBO, cubeVAO;
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &VBO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVerts), cubeVerts, GL_STATIC_DRAW);

	glBindVertexArray(cubeVAO);

	// position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// tex coords
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// setup light VAO
	// -----------------------------
	unsigned int lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// tex coords
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// shared data
	// -----------------------------
	// load textures
	Texture tex1 = Texture::Texture(0, "textures/container.jpg", false);
	tex1.loadTexture();

	Texture tex2 = Texture::Texture(1, "textures/awesomeFace.png", true);
	tex2.loadTexture();
	
	// setup light info
	float l[3];
	float* lightColor = Color::blue.toArray(l);
	glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

	// render loop
	// TODO: double buffering
	while (!glfwWindowShouldClose(window))
	{
		// updates
		// -----------------------------
		time.Update();
		InputInfo inputInfo = input.processInput();
		camera.Update(inputInfo, time);

		// clear buffers
		// -----------------------------
		Color gray = Color::grayMid;
		glClearColor(gray.r, gray.g, gray.b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// draw cube
		// -----------------------------
		shader.useProgram();
		shader.setGlobalVec3Value(lightColor, "lightColor");
		float c[3];
		float* coral = Color::coral.toArray(c);
		std::cout << "coral: " << coral[0] << coral[1] << coral[2] << std::endl;
		shader.setGlobalVec3Value(coral, "albedo");
		shader.setGlobalMatrix4Value(proj, "projection");
		shader.setGlobalMatrix4Value(camera.viewMatrix(), "view");
		glm::mat4 model = glm::mat4(1.0f);
		shader.setGlobalMatrix4Value(model, "model");
		
		// define textures
		shader.setGlobalIntValue(0, "texture1");
		shader.setGlobalIntValue(1, "texture2");
		tex1.bindTexture();
		tex2.bindTexture();

		// draw verts
		glBindVertexArray(cubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// draw light
		// -----------------------------
		lightShader.useProgram();
		lightShader.setGlobalVec3Value(lightColor, "lightColor");
		lightShader.setGlobalMatrix4Value(proj, "projection");
		lightShader.setGlobalMatrix4Value(camera.viewMatrix(), "view");
		glm::mat4 lightModel = glm::mat4(1.0f);
		lightModel = glm::translate(lightModel, lightPos);
		lightModel = glm::scale(lightModel, glm::vec3(0.2f));
		lightShader.setGlobalMatrix4Value(lightModel, "model");

		// draw verts
		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// draw window
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// de-allocate all resources
	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &VBO);
	shader.deallocateProgram();

	// clean up GLFW resources
	glfwTerminate();
	return 0;
}