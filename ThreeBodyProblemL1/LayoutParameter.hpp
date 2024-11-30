#pragma once
#include "Windows.h"
class LayoutParameter {
public:
	const uintptr_t width;
	const uintptr_t height;
	LayoutParameter(uintptr_t _width, uintptr_t _height) :width(_width), height(_height) {};
	LayoutParameter(const LayoutParameter& param) :width(param.width), height(param.height) {};
};