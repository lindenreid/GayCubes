#ifndef _CAMERA_OBJ
#define _CAMERA_OBJ

#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

namespace GayCubes
{
	class Camera
	{
	public:
		Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp);
		
		void Update();

		glm::mat4 viewMatrix() { return glm::lookAt(position, target, worldUp); }

	private:
		glm::vec3 position;
		glm::vec3 target;
		glm::vec3 worldUp;

		glm::vec3 direction () {return glm::normalize(position - target);}
		glm::vec3 right() { return glm::normalize(glm::cross(worldUp, direction()));}
		glm::vec3 localUp() { return glm::cross(direction(), right()); }
	};
}

#endif //_CAMERA_OBJ

