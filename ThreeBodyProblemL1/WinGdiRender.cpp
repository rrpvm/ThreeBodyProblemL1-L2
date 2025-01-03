#include "WinGdiRender.hpp"
#include <string>
#include <math.h>
#include <cmath>
#include "Vector3D.hpp"
#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif
#define SEED_COUNT 128.0F
void WinGdiRender::clear()
{
	static Vector2 origin{ 0,0 };
	HBRUSH brush = CreateSolidBrush(bgColor.toRGB());
	auto oldBrush = SelectObject(deviceContext, brush);
	PatBlt(deviceContext, 0, 0, screenSize.x, screenSize.y, PATCOPY);
	DeleteObject(brush);
	SelectObject(deviceContext, oldBrush);
}
void WinGdiRender::drawWindow( Window& mWindow)
{
	mWindow.draw(this);
}
void WinGdiRender::drawFilledCircle(const Color& circleColor, const Vector2& origin, float radius)
{
	static auto genSeeds = []()->Vector3D* {
		auto arr = new Vector3D[SEED_COUNT];
		double fullCircle = 2.0 * M_PI;
		double step = (fullCircle) / SEED_COUNT;
		int counter = 0;
		for (float i = 0.0; i < fullCircle; i += step) {
			arr[counter].x  = sinf(i);
			arr[counter].y  = cosf(i);
			counter++;
		}
		return arr;
	};
	static Vector3D* flSeesds = genSeeds();
	POINT* points = new POINT[SEED_COUNT];
	for (size_t i = 0; i < SEED_COUNT; ++i) {
		points[i].x = origin.x +  flSeesds[i].x * radius;
		points[i].y = origin.y +  flSeesds[i].y * radius;
	}
	HBRUSH hBrush = CreateSolidBrush(circleColor.toRGB());
	auto old = SelectObject(deviceContext, hBrush);
	Polygon(deviceContext, points, SEED_COUNT);
	DeleteObject(hBrush);
	delete[] points;
	SelectObject(deviceContext, old);
}
void WinGdiRender::drawRect(Color fColor, Vector2 origin, Vector2 size, uintptr_t thickness)
{
	HPEN hPen = CreatePen(PS_SOLID, thickness, fColor.toRGB()); 
	auto old = SelectObject(this->deviceContext, hPen);
	Rectangle(deviceContext, origin.x, origin.y, origin.x + size.x, origin.y + size.y);
	DeleteObject(hPen);
	SelectObject(deviceContext, old);
}
void WinGdiRender::drawRect(Color& fColor, int x0, int y0, size_t width, size_t height, uintptr_t thickness )
{
	HPEN hPen = CreatePen(PS_SOLID, thickness, fColor.toRGB());
	auto oldPen = SelectObject(this->deviceContext, hPen);
	Rectangle(deviceContext, x0, y0, x0 + width, y0 + height);
	DeleteObject(hPen);
	SelectObject(deviceContext, oldPen);
}
void WinGdiRender::drawRect(Color& fColor, int x0, int y0, int width, int height, uintptr_t thickness)
{
}
void WinGdiRender::drawFilledRect(Color fColor, Vector2 origin, Vector2 size)
{
	HBRUSH brush = CreateSolidBrush(fColor.toRGB()); 
	auto oldBrush = SelectObject(this->deviceContext, brush);
	Rectangle(deviceContext, origin.x, origin.y, origin.x + size.x, origin.y + size.y);
	DeleteObject(brush);
	SelectObject(deviceContext, oldBrush);
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

Vector2 WinGdiRender::getTextSize(const std::string& text)
{
	char* buffer = new char[text.length()];
	std::memcpy(buffer, text.c_str(), text.size());
	SIZE rc = {};
	GetTextExtentPoint32(deviceContext, buffer, text.length(), &rc);
	delete[] buffer;
	return Vector2(rc.cx,rc.cy);
}

void WinGdiRender::drawPolygon(const Color& mColor, POINT* points, int size, bool filled)
{
	if (filled) {
		HBRUSH hBrush = CreateSolidBrush(mColor.toRGB());
		auto old = SelectObject(deviceContext, hBrush);
		Polygon(deviceContext, points, size);
		DeleteObject(hBrush);
		SelectObject(deviceContext, old);
	}
	else {
		HPEN hPen = CreatePen(PS_SOLID,1,	mColor.toRGB());
		auto oldPen =  SelectObject(deviceContext, hPen);
		HBRUSH oldBrush = (HBRUSH)SelectObject(deviceContext, GetStockObject(NULL_BRUSH));
		Polyline(deviceContext, points, size);
		DeleteObject(hPen);
		SelectObject(deviceContext, oldBrush);
		SelectObject(deviceContext, oldPen);
	}
}


