#ifndef _WINDOW_INPUT
#define _WINDOW_INPUT

#include <GLAD/glad/glad.h>
#include <glfw-3.3.7/include/GLFW/glfw3.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

namespace GayCubes
{
	class Input
	{
	public:
		static glm::vec4 processInput(GLFWwindow* window);
	};
}

#endif //_WINDOW_INPUT
