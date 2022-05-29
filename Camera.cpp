#include <iostream>
#include <glfw-3.3.7/include/GLFW/glfw3.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

#include "Camera.h"

namespace GayCubes
{
	Camera::Camera(glm::vec3 position, glm::vec3 worldUp)
	{
		this->position = position;
		this->worldUp = worldUp;
	}

	void Camera::Update(glm::vec4 input)
	{
		const float speed = 0.001f;

		glm::vec3 front = this->front();
		glm::vec3 right = this->right();
		position += input.x * speed * front;
		position -= input.y * speed * front;
		position -= input.z * speed * right;
		position += input.w * speed * right;
	}
}