#pragma once
#include <Windows.h>
using USHORT = unsigned short int;
class Color {
private:
	USHORT alpha, red, green, blue;
public:
	Color(USHORT a, USHORT r, USHORT g, USHORT b) {
		this->alpha = a;
		this->red = r;
		this->green = g;
		this->blue = b;
	}
	Color(const Color& c) {
		this->alpha = c.alpha;
		this->red = c.red;
		this->green = c.green;
		this->blue = c.blue;
	}
	Color operator+(const Color& c) const {
		return Color(min(this->alpha + c.alpha, 255), min(this->red + c.red, 255), min(this->green + c.green, 255), min(this->blue + c.blue, 255));
	}
	unsigned long getValue() const {
		return ((alpha << 0) | (red << 8) | (green << 16) | (blue << 24));
	}
	unsigned long toRGB() const {
		return ((red) | (green << 8) | (blue << 16));
	}
};
namespace COLORS {
	const static Color WHITE = Color(255, 255, 255, 255);
	const static Color BLACK = Color(255, 0, 0, 0);
	const static Color ORANGE = Color(255, 255, 165, 0);
	const static Color PRIMARY = ORANGE;
	const static Color PRIMARY_VARIANT = ORANGE + Color(0,0,15,15);
	const static Color ON_PRIMARY = Color(255,255,255,255);
	const static Color SURFACE = Color(255,33,33,33);//bg
	const static Color SURFACE_CONTRAST = Color(255,11,11,11);//borders
	const static Color ON_SURFACE = Color(255,188,188,188);//text
	const static Color SECONDARY_PRIMARY = Color(255,54,54,54);//cards and other
}

