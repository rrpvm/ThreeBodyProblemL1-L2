#include "CheckBoxView.hpp"
#include "IRender.h"
#include <math.h>
void CheckBoxView::draw(IRender* renderer)
{
	int height = (int)measuredHeight;
	int width = (int)measuredWidth;
	
	renderer->drawFilledRect(this->checked ? checkedColor : uncheckedColor, this->viewBound.left, { width,height });
	renderer->drawRect(Color(255, 0, 0, 0), this->viewBound.left, { width,height });
	RECT rect = viewBound.toRect();
	renderer->drawText(std::string("вау"), &rect);
	
}

void CheckBoxView::onAttachedToWindow(Window* wnd)
{
	attachedWindowSize = wnd->getSize();
}

void CheckBoxView::onMeasure()
{

}

void CheckBoxView::measure(uintptr_t availW, uintptr_t availH)
{
	if (widthSize != ViewSizeSpec::HARD || heightSize != ViewSizeSpec::HARD) {
		throw std::exception("unsupported");
	}
	setMeasuredDimension(min(availW, this->width), min(availH, height));
}

void CheckBoxView::onLayout()
{

}
