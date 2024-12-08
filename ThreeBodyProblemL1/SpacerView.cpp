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
	if (widthSize == ViewSizeSpec::WRAP_CONTENT || heightSize == ViewSizeSpec::WRAP_CONTENT) {
		throw std::exception("unsupported(broken logic)");
	}
	int resultWidth = widthSize == ViewSizeSpec::MATCH_PARENT ? availW : min(availW, this->width);
	int resultHeight = heightSize == ViewSizeSpec::MATCH_PARENT ? availH : min(availH, this->height);
	setMeasuredDimension(resultWidth,resultHeight);
}
