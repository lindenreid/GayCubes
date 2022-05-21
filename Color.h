#ifndef _COLORS
#define _COLORS

namespace GayCubes
{
	class Color
	{
	public:
		float r;
		float g;
		float b;

		Color(float r, float g, float b);

		static Color black;
		static Color white;
		static Color red;
		static Color green;
		static Color blue;
		static Color grayLight;
		static Color grayMid;
		static Color grayDark;
	};
}

#endif //_COLORS