#include "SceneLighting.h"

namespace GayCubes
{
	SceneLighting::SceneLighting(Light mainLight)
		: _mainDirectionalLight(mainLight),
			_ambientColor(1.0, 1.0, 1.0)
	{
		// just some temp values
		_ambientStrength = 0.25f;
		_ambientColor.r = 0.8f;
		_ambientColor.g = 0.2f;
		_ambientColor.b = 0.8f;
	}
}