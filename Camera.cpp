#include <glfw-3.3.7/include/GLFW/glfw3.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

#include "Camera.h"

namespace GayCubes
{
	Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp)
	{
		this->position = position;
		this->target = target;
		this->worldUp = worldUp;
	}

	void Camera::Update()
	{
		const float radius = 10.0f;
		float t = glfwGetTime();
		position.x = sin(t) * radius;
		position.z = cos(t) * radius;
	}
}