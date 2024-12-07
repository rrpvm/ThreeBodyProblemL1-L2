#pragma once
#include "Color.h"
#include "Vector2.hpp"
#include "Window.hpp"
class IRender {
protected:
	Vector2 screenSize;
	Color bgColor = Color(255, 255, 255, 255);
public:
	virtual ~IRender() {

	}
	void setScreenSize(const Vector2& screenDimension) {
		this->screenSize = screenDimension;
		onWindowChangeSize();
	}
	int getScreenWidth() {
		return screenSize.x;
	}
	int getScreenHeight() {
		return screenSize.y;
	}
	void setBgColor(const Color& bgColor) {
		this->bgColor = bgColor;
	}
	virtual void clear() = 0;
	virtual void drawWindow(Window& mWindow) = 0;
	virtual void drawFilledCircle(const Color& circleColor, const Vector2& origin, float radius)  =0;
	virtual void drawRect(Color fColor,Vector2 origin,Vector2 size, uintptr_t thickness = 1u) = 0;
	virtual void drawRect(Color& fColor, int x0, int y0, size_t width, size_t height, uintptr_t thickness = 1u) = 0;
	virtual void drawRect(Color& fColor, int x0, int y0, int xEnd, int yEnd, uintptr_t thickness = 1u) = 0;
	virtual void drawFilledRect(Color fColor,Vector2 origin,Vector2 size) = 0;
	virtual void drawFilledRectWithOutline(Color fillColor,Color outlineColor,Vector2 origin,Vector2 size, uintptr_t thickness = 1u) = 0;
	virtual void drawText(const std::string& text, LPRECT lpRect) = 0;
	virtual Vector2 getTextSize(const std::string& text) = 0;
	virtual void drawPolygon(const Color& mColor, POINT* points, int size, bool filled) = 0;
	virtual void startFrame() = 0;
	virtual void endFrame() = 0;
	virtual void onFrame() = 0;
	virtual void onWindowChangeSize() = 0;
};