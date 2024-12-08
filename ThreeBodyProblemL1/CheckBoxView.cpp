#include "CheckBoxView.hpp"
#include "IRender.h"
#include <math.h>
void CheckBoxView::draw(IRender* renderer)
{
	int height = (int)measuredHeight;
	int width = (int)measuredWidth;
	Vector2 renderPosition = this->viewBound.left + mGlobalOffset;



	//lower layer

	renderer->drawFilledRect(this->checked ? checkedColor : uncheckedColor, renderPosition, { width,height });
	
	//upper layer
	static int borderThickness = 2;
	auto borderPosition = renderPosition + Vector2(borderThickness / 2, borderThickness / 2);
	auto borderPositionSize = Vector2(width, height) - Vector2(borderThickness / 2, borderThickness / 2);
	renderer->drawRect(this->borderColor, borderPosition, borderPositionSize, borderThickness);
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
