#include "WinGdiRender.hpp"
#include <string>
#include <math.h>
#include <cmath>
#include "Vector3D.hpp"
#include "ApplicationState.h"
#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif
#define SEED_COUNT 256.0F
void WinGdiRender::clear()
{
	static Vector2 origin{ 0,0 };
	HBRUSH brush = CreateSolidBrush(bgColor.toRGB());
	auto oldBrush = SelectObject(bufferContext, brush);
	PatBlt(bufferContext, 0, 0, screenSize.x, screenSize.y, PATCOPY);
	DeleteObject(brush);
	SelectObject(bufferContext, oldBrush);
}
void WinGdiRender::drawWindow( Window& mWindow)
{
	mWindow.draw(this);
}
void WinGdiRender::drawFilledCircle(const Color& circleColor, const Vector2& origin, float radius)
{
	assert(bufferContext != nullptr && "back buffer nullptr");
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
	auto old = SelectObject(bufferContext, hBrush);
	Polygon(bufferContext, points, SEED_COUNT);
	DeleteObject(old);
	delete[] points;
}
void WinGdiRender::drawRect(Color fColor, Vector2 origin, Vector2 size, uintptr_t thickness)
{
	assert(bufferContext != nullptr && "back buffer nullptr");
	HPEN hPen = CreatePen(PS_SOLID, thickness, fColor.toRGB()); 
	auto oldPen = SelectObject(bufferContext, hPen);
	HBRUSH oldBrush = (HBRUSH)SelectObject(bufferContext, GetStockObject(NULL_BRUSH));
	Rectangle(bufferContext, origin.x, origin.y, origin.x + size.x, origin.y + size.y);
	SelectObject(bufferContext, oldPen);
	DeleteObject(hPen);
	DeleteObject(oldBrush);
}
void WinGdiRender::drawRect(Color& fColor, int x0, int y0, size_t width, size_t height, uintptr_t thickness )
{
	assert(bufferContext != nullptr && "back buffer nullptr");
	HPEN hPen = CreatePen(PS_SOLID, thickness, fColor.toRGB());
	auto oldPen = SelectObject(this->bufferContext, hPen);
	Rectangle(bufferContext, x0, y0, x0 + width, y0 + height);
	DeleteObject(oldPen);
}
void WinGdiRender::drawRect(Color& fColor, int x0, int y0, int width, int height, uintptr_t thickness)
{
	assert(bufferContext != nullptr && "back buffer nullptr");
}
void WinGdiRender::drawFilledRect(Color fColor, Vector2 origin, Vector2 size)
{
	assert(bufferContext != nullptr && "back buffer nullptr");
	HBRUSH brush = CreateSolidBrush(fColor.toRGB());
	RECT rc = { origin.x,origin.y ,origin.x + size.x, origin.y + size.y };
	FillRect(bufferContext, &rc, brush);
	DeleteObject(brush);
}

void WinGdiRender::drawFilledRectWithOutline(Color fillColor, Color outlineColor, Vector2 origin, Vector2 size, uintptr_t thickness)
{
	assert(bufferContext != nullptr && "back buffer nullptr");
	drawFilledRect(fillColor, origin, size);
	drawRect(outlineColor, origin, size,thickness);
}

void WinGdiRender::drawText(const std::string& text, LPRECT lpRect, TextAlign textAlign)
{
	assert(bufferContext != nullptr && "back buffer nullptr");
	SetTextColor(bufferContext, RGB(255, 255, 0));
	SetBkMode(bufferContext, TRANSPARENT);
	char* buffer = new char[text.length()];
	std::memcpy(buffer, text.c_str(), text.size());
	DrawTextEx(bufferContext, buffer, text.length(), lpRect, DT_CENTER, NULL);
	delete[] buffer;
}

Vector2 WinGdiRender::getTextSize(const std::string& text)
{
	assert(bufferContext != nullptr && "back buffer nullptr");
	char* buffer = new char[text.length()];
	std::memcpy(buffer, text.c_str(), text.size());
	SIZE rc = {};
	GetTextExtentPoint32(bufferContext, buffer, text.length(), &rc);
	delete[] buffer;
	return Vector2(rc.cx,rc.cy);
}

void WinGdiRender::drawPolygon(const Color& mColor, POINT* points, int size, bool filled)
{
	assert(bufferContext != nullptr && "back buffer nullptr");
	if (filled) {
		HBRUSH hBrush = CreateSolidBrush(mColor.toRGB());
		auto old = SelectObject(bufferContext, hBrush);
		Polygon(bufferContext, points, size);
		DeleteObject(old);
	}
	else {
		HPEN hPen = CreatePen(PS_SOLID,1,	mColor.toRGB());
		auto oldPen =  SelectObject(bufferContext, hPen);
		HBRUSH oldBrush = (HBRUSH)SelectObject(bufferContext, GetStockObject(NULL_BRUSH));
		Polyline(bufferContext, points, size);
		DeleteObject(oldPen);
		DeleteObject(oldBrush);
	}
}

void WinGdiRender::startFrame()
{
	deviceLock.lock();
	assert(bufferContext != nullptr && "bufferContext doesnt created");
	auto old = SelectObject(bufferContext, buffer);
	DeleteObject(old);
}

void WinGdiRender::endFrame()
{
	if (this->isShowFramesPerSecond) {
		//left,top,right,bottom
		RECT rc;
		std::string fpsString = std::to_string(calcedFps);
		Vector2 textSize = this->getTextSize(fpsString);
		switch (this->mFpsStatPositionOrient)
			{
		case FpsPosition::START: {
			rc = { 0,0,textSize.x,textSize.y };
			break;
		}
		case FpsPosition::TOP_RIGHT: {
			rc = { screenSize.x - textSize.x,0,screenSize.x,textSize.y };
			break;
		}
		case FpsPosition::BOT_LEFT: {
			rc = { 0,screenSize.y - textSize.y,textSize.x,screenSize.y };
			break;
		}
		case FpsPosition::END: {
			rc = { screenSize.x - textSize.x,screenSize.y - textSize.y,screenSize.x,screenSize.y };
			break;
		}
			}
		this->drawText(fpsString, &rc);
	}

	assert(bufferContext != nullptr && "bufferContext doesnt created");
	deviceLock.unlock();
	auto now = GetTickCount64();
	if (GetTickCount64() > lastCalcFrom + 1000) {
		calcedFps = fps;
		fps = 0u;
		lastCalcFrom = now;
	}
	else {
		fps++;
	}
}

void WinGdiRender::onFrame()
{
	deviceLock.lock();
	BitBlt(deviceContext, 0, 0, screenSize.x, screenSize.y, bufferContext, 0, 0, SRCCOPY);
	deviceLock.unlock();
}

void WinGdiRender::onWindowChangeSize()
{
	deviceLock.lock();
	if (this->bufferContext != nullptr) {
		ReleaseDC(appState.windowHWND, this->bufferContext);
		DeleteDC(this->bufferContext);
		bufferContext = nullptr;
	}
	if (this->buffer != nullptr) {
		DeleteObject(this->buffer);
		buffer = nullptr;
	}
	this->bufferContext = CreateCompatibleDC(deviceContext);
	this->buffer = CreateCompatibleBitmap(this->deviceContext, screenSize.x, screenSize.y);
	deviceLock.unlock();
}

void WinGdiRender::startShowFPS(FpsPosition position)
{
	this->isShowFramesPerSecond = true;
	mFpsStatPositionOrient = position;
	//calc the origin of posiiton
}




