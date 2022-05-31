// HelloWorld.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <cmath>

#include <assimp-3.1.1/include/assimp/Importer.hpp>
#include <assimp-3.1.1/include/assimp/scene.h>
#include <assimp-3.1.1/include/assimp/postprocess.h>
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
#include "Material.h"
#include "Mesh.h"
#include "Renderer.h"

using namespace GayCubes;

// resume lighting tutorial from here: https://learnopengl.com/Lighting/Basic-Lighting
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

	// textures
	Texture tex1 = Texture::Texture(0, "textures/container.jpg", false);
	Texture tex2 = Texture::Texture(1, "textures/awesomeFace.png", true);

	// materials
	Material material = Material::Material(shader, tex1, tex2);

	// renderer
	Renderer renderer = Renderer::Renderer("models/backpack.fbx", material);

	// camera
	Camera camera = Camera::Camera(
		(float)windowWidth,
		(float)windowHeight,
		glm::vec3(0.0f, 0.0f, -3.0f),	// position
		glm::vec3(0.0f, 1.0f, 0.0f)		// world up
	);

	// time
	Time time = Time::Time();
	time.Initialize();

	// setup light info
	// TODO: make a Light class
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

		// draw all renderers
		// -----------------------------
		renderer.draw(camera, lightColor);

		// draw window
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// de-allocate all resources
	renderer.deallocate();

	// clean up GLFW resources
	glfwTerminate();
	return 0;
}