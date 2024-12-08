#pragma once
#include <math.h>

class Vector2 {
public:
	int x, y = 0;
public:
	Vector2() {
		x = y = 0;
	}
	Vector2(int _x, int _y) {
		x = _x;
		y = _y;
	}
	Vector2(const Vector2& v) {
		x = v.x;
		y = v.y;
	}
	Vector2 operator+(const Vector2& sum) const  {
		return Vector2(this->x + sum.x, this->y + sum.y);
	}
	void operator+=(Vector2& sum) {
		this->x += sum.x;
		this->y += sum.y;
	}
	Vector2 operator-(Vector2& sum) {
		return Vector2(this->x - sum.x, this->y - sum.y);
	}
	void operator-=(Vector2& sum) {
		this->x -= sum.x;
		this->y -= sum.y;
	}
	int length() {
		return sqrt((x * x) + (y * y));
	}
	int distance(Vector2& vec2) {
		return sqrt(((vec2.x - x) * (vec2.x - x) + (vec2.y - y) * (vec2.y - y)));
	}
private:


};