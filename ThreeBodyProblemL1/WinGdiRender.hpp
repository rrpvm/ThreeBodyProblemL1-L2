#pragma once
#include "Color.h"
#include "Vector2.hpp"
#include "IRender.h"
#include "IRenderStat.h"
#include "Windows.h"
#include <mutex>
class WinGdiRender : public IRender,public IRenderStat {
private:
	HDC deviceContext{ nullptr };
	HDC bufferContext{ nullptr };
	HBITMAP buffer{ nullptr };
	std::mutex deviceLock;
	
public:
	WinGdiRender(HDC _deviceContext) {
		this->deviceContext = _deviceContext;
	}
	virtual void clear() override;
	virtual void drawWindow(Window& mWindow) override;
	virtual void drawFilledCircle(const Color& circleColor, const Vector2& origin, float radius)  override;
	virtual void drawRect(Color fColor,  Vector2 origin,  Vector2 size, uintptr_t thickness = 1u)  override;
	virtual void drawRect(Color& fColor, int x0, int y0, size_t width, size_t height, uintptr_t thickness = 1u)  override;
	virtual void drawRect(Color& fColor, int x0, int y0, int xEnd, int yEnd, uintptr_t thickness = 1u)  override;
	virtual void drawFilledRect(Color fColor, Vector2 origin, Vector2 size) override;
	virtual void drawFilledRectWithOutline(Color fillColor, Color outlineColor, Vector2 origin, Vector2 size, uintptr_t thickness = 1u) override;
	virtual void drawText(const std::string& text, const Color& mColor, LPRECT lpRect, TextAlign textAlign = TextAlign::CENTER) override;
	virtual Vector2 getTextSize(const std::string& text) override;
	virtual void drawPolygon(const Color& mColor, POINT* points, int size, bool filled) override;
	virtual void startFrame();
	virtual void endFrame();
	virtual void onFrame();
	virtual void onWindowChangeSize();
	virtual void startShowFPS(FpsPosition position);
private:
	
};