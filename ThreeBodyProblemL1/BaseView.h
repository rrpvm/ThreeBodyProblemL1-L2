#pragma once
#include "Windows.h"
#include "Color.h"
#include "Renderable.h"	
#include "BoundRect.hpp"
#include <iostream>
class Window;
enum class ViewSizeSpec {
	MATCH_PARENT,
	WRAP_CONTENT,
	HARD
};
class LayoutParameter {
public:
	const uintptr_t width;
	const uintptr_t height;
	LayoutParameter(uintptr_t _width, uintptr_t _height) :width(_width), height(_height) {
		std::cout << _width << "\t" << _height << std::endl;
	};
	LayoutParameter(const LayoutParameter& param) :width(param.width), height(param.height) {};
	
};
class BaseView :IRenderable{
protected:
	ViewSizeSpec widthSize, heightSize;
	LayoutParameter* mViewLayoutParams{new LayoutParameter(0,0)};
	BoundRect mBounds = BoundRect(0,0,0,0);
	BaseView* mParentView{ nullptr };
	Color* mBackgroundColor{ nullptr };
public:
	BaseView(ViewSizeSpec _widthSize, ViewSizeSpec _heightSize) {
		widthSize = _widthSize;
		heightSize = _heightSize;
	}
	BaseView(uintptr_t width, uintptr_t height) {
		widthSize = ViewSizeSpec::HARD;
		heightSize = ViewSizeSpec::HARD;
		setMeasuredDimension(width, height);
	}
	BaseView(ViewSizeSpec _widthSize, uintptr_t height) {
		widthSize =_widthSize;
		heightSize = ViewSizeSpec::HARD;
		setMeasuredDimension(0, height);
	}
	BaseView(uintptr_t width, ViewSizeSpec _heightSpec) {
		widthSize = ViewSizeSpec::HARD;
		heightSize = _heightSpec;
		setMeasuredDimension(width, 0);
	}
	void setBounds(BoundRect rc) {
		this->mBounds = rc;
	}
	virtual void draw(IRender* renderer) = 0;
	virtual void onAttachedToWindow(Window*) = 0;
	virtual void onMeasure() = 0;
	virtual void onLayout() = 0;
	void setBackgroundColor(Color* mColor);
	void requestLayout();
	~BaseView() {

	}
protected:
	void setMeasuredDimension(uintptr_t measuredWidth, uintptr_t measuredHeight) {
		if (mViewLayoutParams != nullptr) {
			delete mViewLayoutParams;
		}
		this->mViewLayoutParams = new LayoutParameter(measuredWidth, measuredHeight);
	}
private:

};