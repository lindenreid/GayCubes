#include "Time.h"

#include <glfw-3.3.7/include/GLFW/glfw3.h>

namespace GayCubes
{
	void Time::Initialize()
	{
		_deltaTime = 0.0f;
		_lastFrame = 0.0f;
	}

	void Time::Update()
	{
		float currentTime = GetTime();
		_deltaTime = currentTime - _lastFrame;
		_lastFrame = currentTime;
	}
}