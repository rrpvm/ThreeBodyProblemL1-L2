#include "SelectableButton.hpp"
#include "IRender.h"
#include "Utils.hpp"
bool SelectableButton::onMouseEvent(const MouseEvent& mouseEvent)
{
	bool isInPoint = Utils::isPointInBB({ mouseEvent.x,mouseEvent.y }, getAbsoluteOrigin(), getSize());
	isHovered = isInPoint;
	if (isInPoint && mouseEvent.isMouseClickedNow) {
		mListener->invoke();
	}
	else if (mouseEvent.isMouseClickedNow) {

	}
	return isInPoint;
}

void SelectableButton::draw(IRender* renderer)
{
	int height = (int)measuredHeight;
	int width = (int)measuredWidth;
	auto textSize = renderer->getTextSize(this->buttonText);
	RECT drawRect = (viewBound + mGlobalOffset).toRect();
	drawRect.top += textPositionOffset.y;
	drawRect.bottom -= textPositionOffset.y;
	if (isSelected) {
		renderer->drawFilledRect(Color(255,255,255,255), mGlobalPosition, {width,height});
	}
	else {
		renderer->drawRect(isHovered ? this->borderHoverColor : this->borderColor, mGlobalPosition, { width,height }, this->borderThickness);
	}
	renderer->drawText(this->buttonText, &drawRect, TextAlign::CENTER);
}

void SelectableButton::onAttachedToWindow(Window*)
{
}
void SelectableButton::onMeasure()
{
}

void SelectableButton::measure(uintptr_t availW, uintptr_t availH)
{
	if (this->widthSize == ViewSizeSpec::HARD && this->heightSize == ViewSizeSpec::HARD) {
		setMeasuredDimension(min(availW, this->width), min(availH, height));
		auto textSize = this->calcTextSize(this->buttonText);
		textPositionOffset = { 0, (int)height / 2 - textSize.y / 2 };
		return;
	}
	int resultWidth = 0;
	int resultHeight = 0;
	auto textSize = this->calcTextSize(this->buttonText);
	if (heightSize == ViewSizeSpec::HARD) {
		resultHeight = min(availH, height);
	}
	else if (heightSize == ViewSizeSpec::WRAP_CONTENT) {
		resultHeight = min(textSize.y + buttonPadding.y * 2, availH);
	}
	else if (heightSize == ViewSizeSpec::MATCH_PARENT) {
		resultHeight = availH;
	}
	if (widthSize == ViewSizeSpec::MATCH_PARENT) {
		resultWidth = availW;
	}
	else if (widthSize == ViewSizeSpec::WRAP_CONTENT) {
		//padding left + padding right + text size
		resultWidth = min(textSize.x + buttonPadding.x * 2, availW);
	}
	else if (widthSize == ViewSizeSpec::HARD) {
		resultWidth = min(availW, width);
	}
	textPositionOffset = { 0, (int)resultHeight / 2 - textSize.y / 2 };
	setMeasuredDimension(resultWidth, resultHeight);
}

void SelectableButton::onLayout()
{
}
