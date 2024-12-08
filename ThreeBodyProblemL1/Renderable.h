#pragma once
#include "Vector2.hpp"
class IRender;
class IRenderable {
public:
	IRenderable() {

	}
	~IRenderable() {

	}
	virtual void draw(IRender* renderer) = 0;
	Vector2 calcTextSize(const char* text);
};