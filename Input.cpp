#include <GLAD/glad/glad.h>
#include <glfw-3.3.7/include/GLFW/glfw3.h>

#include "Input.h"

namespace GayCubes
{
	glm::vec4 Input::processInput(GLFWwindow* window)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, true);
		}

		glm::vec4 input = glm::vec4(0.0f);
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			input.x = 1;
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			input.y = 1;
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			input.z = 1;
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			input.w = 1;
		}

		return input;
	}
}