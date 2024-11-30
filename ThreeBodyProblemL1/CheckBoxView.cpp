#include "CheckBoxView.hpp"
#include "IRender.h"
#include <math.h>
void CheckBoxView::draw(IRender* renderer)
{
	int height = (int)measuredHeight;
	int width = (int)measuredWidth;
	/*
	renderer->drawFilledRect(this->checked ? checkedColor : uncheckedColor, this->mBounds.left, { width,height });
	renderer->drawRect(Color(255, 0, 0, 0), this->mBounds.left, { width,height });
	auto rect = RECT{ (LONG)mBounds.left.x, (LONG)mBounds.left.y, (LONG)mBounds.right.x, (LONG)mBounds.right.y };
	renderer->drawText(std::string("вау"), &rect);
	*/
}

void CheckBoxView::onAttachedToWindow(Window*)
{

}

void CheckBoxView::onMeasure()
{
	/*int boundHeight = this->mBounds.right.y - this->mBounds.left.y;
	int height = min(boundHeight, measuredHeight);
	setMeasuredDimension(measuredWidth, height);*/
}

void CheckBoxView::measure(uintptr_t availW, uintptr_t availH)
{

}

void CheckBoxView::onLayout()
{

}
