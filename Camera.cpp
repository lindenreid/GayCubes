#include <iostream>
#include <glfw-3.3.7/include/GLFW/glfw3.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

#include "Camera.h"
#include "Time.h"

namespace GayCubes
{
	Camera::Camera(float windowWidth, float windowHeight, glm::vec3 position, glm::vec3 worldUp)
	{
		this->_position = position;
		this->_worldUp = worldUp;

		yaw = -90.0f;
		pitch = 0.0f;

		_projection = glm::perspective(glm::radians(45.0f), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
	}

	void Camera::Update(InputInfo input, Time time)
	{
		const float speed = 2.5f * time.DeltaTime();

		glm::vec3 front = this->_front;
		glm::vec3 right = this->right();
		_position += input.wasd.x * speed * front;
		_position -= input.wasd.y * speed * front;
		_position -= input.wasd.z * speed * right;
		_position += input.wasd.w * speed * right;

		glm::vec3 direction = glm::vec3(0.0f);

		yaw += input.mouse.z * _sensitivity;
		pitch -= input.mouse.w * _sensitivity;
		if (pitch > 89.0f)
		{
			pitch = 89.0f;
		}
		else if (pitch < -89.0f)
		{
			pitch = -89.0f;
		}

		direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		direction.y = sin(glm::radians(pitch));
		direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

		_front = glm::normalize(direction);
	}
}