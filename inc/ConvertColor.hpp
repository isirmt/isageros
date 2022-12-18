#include <array>
#pragma once

namespace GLSYS
{
	struct ColorDouble
	{
		double r;
		double g;
		double b;
		double a;
	};
	class ConvertColor
	{
	public:
		ConvertColor() {}
		ConvertColor(int r, int g, int b, int a = 0);
		~ConvertColor() {}

		void Create(int r, int g, int b, int a = 0);

		ColorDouble GetColor() { return color; }

	private:
		void InsertValue(int r, int g, int b, int a);
		ColorDouble color;
	};
}