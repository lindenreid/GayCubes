// HelloWorld.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <cmath>
#include <vector>

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
#include "Light.h"
#include "SceneLighting.h"

using namespace GayCubes;

// General TODOs
// textures: don't load same texture multiple times
// next tut: https://learnopengl.com/Advanced-OpenGL/Stencil-testing
int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
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

	// load textures
	// -----------------------------
	Texture albedoTex = Texture::Texture(0, "../resources/models/deer/textures/albedo.png", false);
	Texture roughnessTex = Texture::Texture(1, "../resources/models/deer/textures/roughness.jpg", false);

	// deer model renderer
	// -----------------------------
	ShaderProgram shader = ShaderProgram::ShaderProgram("shaders/litVertex.glsl", "shaders/litFrag.glsl");
	Material material = Material::Material(shader, albedoTex, roughnessTex, 1.0f);
	Renderer renderer = Renderer::Renderer("../resources/models/deer/deer.obj", material);

	// camera
	// -----------------------------
	Camera camera = Camera::Camera(
		(float)windowWidth,
		(float)windowHeight,
		glm::vec3(0.0f, 0.0f, -3.0f),	// position
		glm::vec3(0.0f, 1.0f, 0.0f)		// world up
	);

	// time
	// -----------------------------
	Time time = Time::Time();
	time.Initialize();

	// light
	// -----------------------------
	glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
	glm::vec3 lightDir(0.0f, -1.0f, 0.0f);
	Color lightColor = Color(0.7f, 0.7f, 1.0f);
	SceneLighting lighting = SceneLighting(Light(1.0f, lightPos, lightDir, lightColor));

	// light debug renderer
	// -----------------------------
	ShaderProgram lightShader = ShaderProgram::ShaderProgram("shaders/lightVertex.glsl", "shaders/lightFrag.glsl");
	Material lightMat = Material::Material(lightShader, albedoTex, roughnessTex, 0.0f); // TODO: material constructor that doesn't require textures
	Renderer lightRenderer = Renderer::Renderer("../resources/models/oval.obj", lightMat);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

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

		// move light around
		glm::mat4 trans = glm::mat4(1.0f);
		float t = time.GetTime();
		float radius = 5.0f;
		float speed = 1.0f;
		lighting._mainDirectionalLight._direction.x = std::sin(t * speed) * radius;
		lighting._mainDirectionalLight._direction.z = std::cos(t * speed) * radius;
		lighting._mainDirectionalLight._direction = glm::normalize(lighting._mainDirectionalLight._direction);

		// draw all renderers
		// -----------------------------
		renderer.draw(camera, lighting._mainDirectionalLight, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
		lightRenderer.draw(camera, lighting._mainDirectionalLight, lighting._mainDirectionalLight._position, glm::vec3(0.2f, 0.2f, 0.2f));

		// draw window
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// de-allocate all resources
	renderer.deallocate();
	lightRenderer.deallocate();

	// clean up GLFW resources
	glfwTerminate();
	return 0;
}