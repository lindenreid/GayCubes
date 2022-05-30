#include "Color.h"

namespace GayCubes
{
	Color::Color(float r, float g, float b)
	{
		this->r = r;
		this->g = g;
		this->b = b;
	}

	float* Color::toArray(float arr[3])
	{
		arr[0] = r;
		arr[1] = g;
		arr[2] = b;
		return arr;
	}

	Color Color::black =	Color(0, 0, 0);
	Color Color::white =	Color(1, 1, 1);
	
	Color Color::red =		Color(1, 0, 0);
	Color Color::green =	Color(0, 1, 0);
	Color Color::blue =		Color(0, 0, 1);

	Color Color::grayLight =	Color(0.25f, 0.25f, 0.25f);
	Color Color::grayMid =		Color(0.50f, 0.50f, 0.50f);
	Color Color::grayDark =		Color(0.75f, 0.75f, 0.75f);

	Color Color::coral =	Color(1.0f, 0.5f, 0.31f);
}