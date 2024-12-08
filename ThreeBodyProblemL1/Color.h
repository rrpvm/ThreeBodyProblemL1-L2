#pragma once
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
	unsigned long getValue() const {
		return ((alpha << 0) | (red << 8) | (green << 16) | (blue << 24));
	}
	unsigned long toRGB() const {
		return ((red) | (green << 8) | (blue << 16));
	}
};
static Color WHITE = Color(255, 255, 255, 255);
static Color BLACK = Color(255, 0, 0, 0);
