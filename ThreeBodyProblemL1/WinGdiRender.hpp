#pragma once
#include "Color.h"
#include "Vector2.hpp"
#include "IRender.h"
#include "Windows.h"

class WinGdiRender : public IRender {
private:
	HDC deviceContext;
public:
	WinGdiRender(HDC _deviceContext) {
		this->deviceContext = _deviceContext;
	}
	virtual void drawWindow(Window& mWindow) override;
	virtual void drawRect(Color fColor,  Vector2 origin,  Vector2 size, uintptr_t thickness = 1u)  override;
	virtual void drawRect(Color& fColor, int x0, int y0, size_t width, size_t height, uintptr_t thickness = 1u)  override;
	virtual void drawRect(Color& fColor, int x0, int y0, int xEnd, int yEnd, uintptr_t thickness = 1u)  override;
	virtual void drawFilledRect(Color fColor, Vector2 origin, Vector2 size) override;
	virtual void drawFilledRectWithOutline(Color fillColor, Color outlineColor, Vector2 origin, Vector2 size, uintptr_t thickness = 1u) override;
	virtual void drawText(const std::string& text, LPRECT lpRect) override;
private:
	
};