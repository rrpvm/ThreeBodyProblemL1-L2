#pragma once
#include "Vector2.hpp"
class Utils {
public:
	static bool isPointInBB(const Vector2& obj, const Vector2& bbBox, const Vector2& bbBoxSize);
};