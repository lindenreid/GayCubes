#include "Light.h"

#include <glm/glm/glm.hpp>
#include "Color.h"

namespace GayCubes
{
	// ------------------------------------------------------------------------
	Light::Light(
		float strength,
		glm::vec3 position,
		glm::vec3 direction,
		Color color
	) : _color(color)
	{
		_strength = strength;
		_position = position;
		_direction = direction;
	}
}