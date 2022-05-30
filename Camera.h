#ifndef _CAMERA_OBJ
#define _CAMERA_OBJ

#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

#include "Time.h"

namespace GayCubes
{
	class Camera
	{
	public:
		Camera(glm::vec3 position, glm::vec3 worldUp);
		
		void Update(glm::vec4 input, Time time);

		glm::mat4 viewMatrix() { return glm::lookAt(position, position+front(), worldUp); }

	private:
		glm::vec3 position;
		glm::vec3 worldUp;

		glm::vec3 front() { return glm::vec3(0.0f, 0.0f, -1.0f); }
		glm::vec3 right() { return glm::normalize(glm::cross(front(), worldUp)); };
	};
}

#endif //_CAMERA_OBJ

