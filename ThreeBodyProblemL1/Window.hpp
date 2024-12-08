#pragma once
#include "ParentView.hpp"
#include "Color.h"
#include "Vector2.hpp"
#include "Renderable.h"
#include "MouseEvent.hpp"
#include <vector>
class Window : IRenderable {
private:
	uintptr_t mWidth{ 0u }, mHeight{ 0u };
	Color mBackgroundColor{ Color(255,0,0,0) };
private:
	Vector2 origin{ 0,0 };
	Vector2 size{static_cast<int>(mWidth),static_cast<int>(mHeight) };
	ParentView* mRootView{ nullptr };
	bool isDragging = false;
	DWORD timeStartDragging{ 0 };
public:
	Window(uintptr_t _width,
		uintptr_t _height,
		Color backgroundColor
	); 
	~Window() {
		//хоть кто-то когда-то этот код прочитает?
	}
	void setView(ParentView* mView);
	void processMouseEvent(const MouseEvent& mouseEvent);
	virtual void draw(IRender* renderer);
	void setOrigin(const Vector2& origin) {
		this->origin = origin;
		mRootView->onGlobalOffsetChanged(origin);
	}
	void setBgColor(const Color& bgColor) {
		this->mBackgroundColor = bgColor;
	}
	Color getColor() const {
		return this->mBackgroundColor;
	}
	const Vector2& getSize() {
		return this->size;
	}
};