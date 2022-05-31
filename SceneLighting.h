#ifndef _SCENE_LIGHTING
#define _SCENE_LIGHTING

#include <glm/glm/glm.hpp>

#include "Color.h"
#include "Light.h"

namespace GayCubes
{
	class SceneLighting
	{
	public:
		SceneLighting(Light mainLight);

		Light _mainDirectionalLight;
		float _ambientStrength;
		Color _ambientColor;
	};
}

#endif //_SCENE_LIGHTING

