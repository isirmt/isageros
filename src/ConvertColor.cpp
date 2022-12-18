#include "ConvertColor.hpp"

using namespace GLSYS;

ConvertColor::ConvertColor(int r, int g, int b, int a)
{
	InsertValue(r, g, b, a);
}

void ConvertColor::Create(int r, int g, int b, int a)
{
	InsertValue(r, g, b, a);
}

void ConvertColor::InsertValue(int r, int g, int b, int a)
{
	int colorIntMax = 255;
	color.r = (float)r / (float)colorIntMax;
	color.g = (float)g / (float)colorIntMax;
	color.b = (float)b / (float)colorIntMax;
	color.a = (float)a / (float)colorIntMax;
}