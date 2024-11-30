#include "WinGdiRender.hpp"
#include <string>
void WinGdiRender::drawWindow( Window& mWindow)
{
	mWindow.draw(this);
}
void WinGdiRender::drawRect(Color fColor, Vector2 origin, Vector2 size, uintptr_t thickness)
{
	HPEN hPen = CreatePen(PS_SOLID, thickness, fColor.toRGB()); 
	SelectObject(this->deviceContext, hPen);
	Rectangle(deviceContext, origin.x, origin.y, origin.x + size.x, origin.y + size.y);
	DeleteObject(hPen);
}
void WinGdiRender::drawRect(Color& fColor, int x0, int y0, size_t width, size_t height, uintptr_t thickness )
{
	HPEN hPen = CreatePen(PS_SOLID, thickness, fColor.toRGB());
	SelectObject(this->deviceContext, hPen);
	Rectangle(deviceContext, x0, y0, x0 + width, y0 + height);
	DeleteObject(hPen);
}
void WinGdiRender::drawRect(Color& fColor, int x0, int y0, int width, int height, uintptr_t thickness)
{
}
void WinGdiRender::drawFilledRect(Color fColor, Vector2 origin, Vector2 size)
{
	HBRUSH brush = CreateSolidBrush(fColor.toRGB()); 
	SelectObject(this->deviceContext, brush);
	Rectangle(deviceContext, origin.x, origin.y, origin.x + size.x, origin.y + size.y);
	DeleteObject(brush);
}

void WinGdiRender::drawFilledRectWithOutline(Color fillColor, Color outlineColor, Vector2 origin, Vector2 size, uintptr_t thickness)
{
	drawFilledRect(fillColor, origin, size);
	drawRect(outlineColor, origin, size,thickness);
}

void WinGdiRender::drawText(const std::string& text, LPRECT lpRect)
{
	SetTextColor(deviceContext, RGB(255, 0, 0));
	SetBkMode(deviceContext, TRANSPARENT);
	char* buffer = new char[text.length()];
	std::memcpy(buffer, text.c_str(), text.size());
	DrawTextEx(deviceContext, buffer, text.length(), lpRect, DT_CENTER, NULL);
	delete[] buffer;
}


