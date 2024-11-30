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
class BaseView :IRenderable{
protected:
	BaseView* mParentView{ nullptr };
protected:
	Color* mBackgroundColor{ nullptr };
protected:
	ViewSizeSpec widthSize, heightSize;
	LayoutParameter* mViewLayoutParams{new LayoutParameter(0,0)};
public:
	std::string debugId;
	uintptr_t measuredWidth{ 0u }, measuredHeight{ 0u };
	BaseView(const char* _debugId,	ViewSizeSpec _widthSize, ViewSizeSpec _heightSize) {
		debugId = std::string(_debugId);
		widthSize = _widthSize;
		heightSize = _heightSize;
	}
	BaseView(const char* _debugId, uintptr_t width, uintptr_t height) {
		debugId = std::string(_debugId);
		widthSize = ViewSizeSpec::HARD;
		heightSize = ViewSizeSpec::HARD;
		setMeasuredDimension(width, height);
	}
	BaseView(const char* _debugId, ViewSizeSpec _widthSize, uintptr_t height) {
		debugId = std::string(_debugId);
		widthSize =_widthSize;
		heightSize = ViewSizeSpec::HARD;
		setMeasuredDimension(0, height);
	}
	BaseView(const char* _debugId, uintptr_t width, ViewSizeSpec _heightSpec) {
		debugId = std::string(_debugId);
		widthSize = ViewSizeSpec::HARD;
		heightSize = _heightSpec;
		setMeasuredDimension(width, 0);
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
	
	void requestLayout();
	void onAttachedToView(BaseView* view) {
		this->mParentView = view;
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