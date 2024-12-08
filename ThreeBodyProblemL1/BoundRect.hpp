#pragma once
#include "Vector2.hpp"
#include "assert.h"
class BoundRect {
public:
	Vector2 left{ 0,0 }, right{ 0,0 };
	BoundRect(int x0, int y0, int x1, int y1) {
		this->left = { x0,y0 };
		this->right = { x1,y1 };
		assert(x1 >= x0 && y1 >= y0 && "invalid bound rect");

	}
	BoundRect() {

	}
	RECT toRect() {
		return RECT{ static_cast<LONG>(left.x), static_cast<LONG>(left.y), static_cast<LONG>(right.x), static_cast<LONG>(right.y) };
	}
	Vector2 size() {
		return { right.x - left.x, right.y - left.y };
	}
	BoundRect operator+(const Vector2& offset) {
		auto result = BoundRect();
		result.left = left + offset;
		result.right = right + offset;
		return result;
	}
};