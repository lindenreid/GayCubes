#include <iostream>
#include <GLAD/glad/glad.h>
#include <glfw-3.3.7/include/GLFW/glfw3.h>

#include "Input.h"

namespace GayCubes
{
	Input::Input(GLFWwindow* window)
	{
		_window = window;
		_firstFrame = true;

		// hide cursor and capture it
		glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	InputInfo Input::processInput()
	{
		InputInfo output;

		if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(_window, true);
		}

		glm::vec4 wasd = glm::vec4(0.0f);
		if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS)
		{
			wasd.x = 1;
		}
		if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS)
		{
			wasd.y = 1;
		}
		if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS)
		{
			wasd.z = 1;
		}
		if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS)
		{
			wasd.w = 1;
		}
		output.wasd = wasd;

		double x, y;
		glfwGetCursorPos(_window, &x, &y);
		float xpos = static_cast<float>(x);
		float ypos = static_cast<float>(y);
		
		/*
		if (_firstFrame)
		{
			_lastX = (float)xpos;
			_lastY = (float)ypos;
			_firstFrame = false;
		}
		*/

		std::cout << "xy: " << xpos << "," << ypos << std::endl;
		std::cout << "last xy: " << _lastX << "," << _lastY << std::endl;
		
		output.mouse = glm::vec4(
			xpos,
			ypos,
			xpos - _lastX,
			ypos - _lastY
		);
		_lastX = xpos;
		_lastY = ypos;

		std::cout << "zw: " << output.mouse.z << "," << output.mouse.w << std::endl;

		return output;
	}
}