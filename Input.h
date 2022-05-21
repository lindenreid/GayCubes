#ifndef _WINDOW_INPUT
#define _WINDOW_INPUT

#include <GLAD/glad/glad.h>
#include <glfw-3.3.7/include/GLFW/glfw3.h>

namespace GayCubes
{
	class Input
	{
	public:
		static void processInput(GLFWwindow* window);
	};
}

#endif //_WINDOW_INPUT
