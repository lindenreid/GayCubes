#ifndef _TIME_HELPERS
#define _TIME_HELPERS

#include <glfw-3.3.7/include/GLFW/glfw3.h>

namespace GayCubes
{
	class Time
	{
	public:
		void Initialize();
		void Update();
		float DeltaTime() { return _deltaTime; };
		float GetTime() { return (float)glfwGetTime(); }

	private:
		float _deltaTime;
		float _lastFrame;
	};
}

#endif _TIME_HELPERS

