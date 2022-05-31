#ifndef _LIGHT_OBJ
#define _LIGHT_OBJ

#include <glm/glm/glm.hpp>
#include "Color.h"

namespace GayCubes
{
	class Light
	{
	public: 
		Light(float strength, glm::vec3 position, glm::vec3 direction, Color color);

		float _strength;
		glm::vec3 _position;
		glm::vec3 _direction;
		Color _color;
	};
}

#endif //_LIGHT_OBJ

