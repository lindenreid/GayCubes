#ifndef _CAMERA_OBJ
#define _CAMERA_OBJ

#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

#include "Input.h"
#include "Time.h"

namespace GayCubes
{
	class Camera
	{
	public:
		Camera(float windowWidth, float windowHeight, glm::vec3 position, glm::vec3 worldUp);
		
		void Update(InputInfo input, Time time);

		glm::mat4 viewMatrix() { return glm::lookAt(_position, _position+_front, _worldUp); }
		glm::mat4 projection() { return _projection; }

	private:
		const float _sensitivity = 0.05f;
		float yaw;
		float pitch;

		glm::mat4 _projection;

		glm::vec3 _position;
		glm::vec3 _worldUp;

		glm::vec3 _front = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 right() { return glm::normalize(glm::cross(_front, _worldUp)); };
	};
}

#endif //_CAMERA_OBJ

