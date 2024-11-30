#include "SpacerView.hpp"

void SpacerView::draw(IRender* renderer)
{
}

void SpacerView::onAttachedToWindow(Window*)
{
}

void SpacerView::onMeasure()
{
}

void SpacerView::onLayout()
{

}

void SpacerView::measure(uintptr_t availW, uintptr_t availH)
{
	if (widthSize != ViewSizeSpec::HARD || heightSize != ViewSizeSpec::HARD) {
		throw std::exception("unsupported");
	}
	setMeasuredDimension(min(availW, this->width), min(availH, height));
}
