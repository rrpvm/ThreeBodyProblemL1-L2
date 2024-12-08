#pragma once
#include "LayoutParameter.hpp"
#include "Renderable.h"	
#include "Color.h"
#include "BoundRect.hpp"
#include <iostream>
class Window;
enum class ViewSizeSpec {
	MATCH_PARENT,
	WRAP_CONTENT,
	HARD
};

//onAttach->onMeasure->onLayout->onDraw();
//requestLayout() отправляет цепь в onMeasure
//invalidate() -> onDraw();
class BaseView :protected IRenderable {
protected:
	BaseView* mParentView{ nullptr };
	uintptr_t width{ 0u }, height{ 0u };
	BoundRect viewBound;
	Vector2 mGlobalOffset{ 0,0 };
protected:
	Color* mBackgroundColor{ nullptr };
public:
	ViewSizeSpec widthSize, heightSize;
	LayoutParameter* mViewLayoutParams{ new LayoutParameter(0,0) };
	Vector2 attachedWindowSize;

public:
	std::string debugId;
	uintptr_t measuredWidth{ 0u }, measuredHeight{ 0u };
	BaseView(const char* _debugId, ViewSizeSpec _widthSize, ViewSizeSpec _heightSize) {
		debugId = std::string(_debugId);
		widthSize = _widthSize;
		heightSize = _heightSize;
	}
	BaseView(const char* _debugId, uintptr_t _width, uintptr_t _height) {
		debugId = std::string(_debugId);
		widthSize = ViewSizeSpec::HARD;
		heightSize = ViewSizeSpec::HARD;
		width = _width;
		height = _height;
	}
	BaseView(const char* _debugId, ViewSizeSpec _widthSize, uintptr_t _height) {
		debugId = std::string(_debugId);
		widthSize = _widthSize;
		heightSize = ViewSizeSpec::HARD;
		height = _height;

	}
	BaseView(const char* _debugId, uintptr_t _width, ViewSizeSpec _heightSpec) {
		debugId = std::string(_debugId);
		widthSize = ViewSizeSpec::HARD;
		heightSize = _heightSpec;
		width = _width;
	}
	//render view
	virtual void draw(IRender* renderer) = 0;
	//callback when attach
	virtual void onAttachedToWindow(Window*) = 0;
	//callback  when measure. 
	virtual void onMeasure() = 0;

	virtual void measure(uintptr_t availW, uintptr_t availH) = 0;
	//callback when layout view. only for parentview
	virtual void onLayout() = 0;
	//window changed position
	virtual void onGlobalOffsetChanged(const Vector2& globalOffsetChanged) {
		this->mGlobalOffset = globalOffsetChanged;
	}
	//recalc view
	void requestLayout();


	void onAttachedToView(BaseView* view) {
		this->mParentView = view;
		attachedWindowSize = view->attachedWindowSize;
	}
	BoundRect& getBoundRect() {
		return this->viewBound;
	}
	void setBoundRect(const BoundRect& mBound) {
		this->viewBound = mBound;
	}
	
public:
	void setBackgroundColor(Color* mColor);//ui bg color
	virtual ~BaseView() {

	}
protected:
	void setMeasuredDimension(uintptr_t measuredWidth, uintptr_t measuredHeight) {
		if (mViewLayoutParams != nullptr) {
			delete mViewLayoutParams;
		}
		this->measuredWidth = measuredWidth;
		this->measuredHeight = measuredHeight;
		this->mViewLayoutParams = new LayoutParameter(measuredWidth, measuredHeight);
	}
private:

};