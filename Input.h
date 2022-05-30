#ifndef _WINDOW_INPUT
#define _WINDOW_INPUT

#include <glfw-3.3.7/include/GLFW/glfw3.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

namespace GayCubes
{
	struct InputInfo
	{
		glm::vec4 wasd;
		glm::vec4 mouse; //xpos, ypos, xoffset, yoffset
	};

	class Input
	{
	public:
		Input(GLFWwindow* window);
		InputInfo processInput();

	private:
		GLFWwindow* _window;
		float _lastX;
		float _lastY;
		bool _firstFrame;
	};
}

#endif //_WINDOW_INPUT
