#pragma once
#include "ParentView.hpp"
#include "Color.h"
#include "Vector2.hpp"
#include "Renderable.h"
#include <vector>
class Window : IRenderable {
private:
	uintptr_t mWidth{ 0u }, mHeight{ 0u };
	Color mBackgroundColor{ Color(255,0,0,0) };
private:
	Vector2 origin{ 0,0 };
	Vector2 size{static_cast<int>(mWidth),static_cast<int>(mHeight) };
	ParentView* mParentView{ nullptr };
public:
	Window(uintptr_t _width,
		uintptr_t _height,
		Color backgroundColor
	) {
		this->mWidth = _width;
		this->mHeight = _height;
		this->mBackgroundColor = backgroundColor;
		this->size = { static_cast<int>(_width),static_cast<int>(_height) };
	}
	Color getColor() const {
		return this->mBackgroundColor;
	}
	void setView(ParentView* mView);
	virtual void draw(IRender* renderer);
	~Window() {
		
	}
};