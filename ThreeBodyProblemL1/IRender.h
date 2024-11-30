#pragma once
#include "Color.h"
#include "Vector2.hpp"
#include "Window.hpp"
class IRender {
private:

public:
	~IRender() {

	}
	virtual void drawWindow( Window& mWindow) = 0;
	virtual void drawRect(Color fColor,Vector2 origin,Vector2 size, uintptr_t thickness = 1u) = 0;
	virtual void drawRect(Color& fColor, int x0, int y0, size_t width, size_t height, uintptr_t thickness = 1u) = 0;
	virtual void drawRect(Color& fColor, int x0, int y0, int xEnd, int yEnd, uintptr_t thickness = 1u) = 0;
	virtual void drawFilledRect(Color fColor,Vector2 origin,Vector2 size) = 0;
	virtual void drawFilledRectWithOutline(Color fillColor,Color outlineColor,Vector2 origin,Vector2 size, uintptr_t thickness = 1u) = 0;
	virtual void drawText(const std::string& text, LPRECT lpRect) = 0;
};