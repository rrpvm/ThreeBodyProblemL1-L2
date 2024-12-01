#pragma once
#include <math.h>
class Vector3D {
public:
	float x{ 0.0F }, y{ 0.0F }, z{ 0.0F };
public:
	Vector3D() {
		x = y = z = 0.0F;
	}
	Vector3D(float _x, float _y, float _z) {
		x = _x;
		y = _y;
		z = _z;
	}
	Vector3D(const Vector3D& v) {
		x = v.x;
		y = v.y;
		z = v.z;
	}
	Vector3D operator+(Vector3D& sum) {
		return Vector3D(this->x + sum.x, this->y + sum.y, this->z + sum.z);
	}
	Vector3D& operator+=(const Vector3D& sum) {
		this->x += sum.x;
		this->y += sum.y;
		this->z += sum.z;
		return *this;
	}
	Vector3D operator-(Vector3D& sum)const {
		return Vector3D(this->x - sum.x, this->y - sum.y, this->z - sum.z);
	}
	Vector3D operator*(float fl) {
		return Vector3D(this->x * fl, this->y * fl, this->z * fl);
	}
	void normalize() {
		auto ln = length();
		if (ln != 0) {
			x /= ln;
			y /= ln;
			z /= ln;
		}
	}
	void operator-=(Vector3D& sum) {
		this->x -= sum.x;
		this->y -= sum.y;
		this->z -= sum.z;
	}
	double length() {
		return sqrt((x * x) + (y * y) + (z*z));
	}
	double distance(Vector3D& vec3) const {
		return sqrt(((vec3.x - x) * (vec3.x - x) + (vec3.y - y) * (vec3.y - y) + (vec3.z - z) * (vec3.z- z)));
	}
};