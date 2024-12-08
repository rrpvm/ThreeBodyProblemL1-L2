#include "CheckBoxView.hpp"
#include "IRender.h"
#include <math.h>
#include "Utils.hpp"
bool CheckBoxView::onMouseEvent(const MouseEvent& mouseEvent)
{
	bool isInPoint = Utils::isPointInBB({ mouseEvent.x,mouseEvent.y }, getAbsoluteOrigin(), getSize());
	if (isInPoint && mouseEvent.isMouseClickedNow) {
		onClicked();
	}

	return false;
}
void CheckBoxView::draw(IRender* renderer)
{
	int height = (int)measuredHeight;
	int width = (int)measuredWidth;
	Vector2 renderPosition = this->viewBound.left + mGlobalOffset;



	//lower layer
	auto cbSize = Vector2(checkboxSize, checkboxSize);
	renderer->drawFilledRect(this->checked ? checkedColor : uncheckedColor, renderPosition, cbSize);
	
	//upper layer
	static int borderThickness = 2;
	auto borderPosition = renderPosition + Vector2(borderThickness / 2, borderThickness / 2);
	auto borderPositionSize = cbSize - Vector2(borderThickness / 2, borderThickness / 2);
	renderer->drawRect(this->checked ? activeBorderColor : borderColor, borderPosition, borderPositionSize, borderThickness);

	//text
	Vector2 textRenderPosition = textPosition + mGlobalOffset;
	auto centerY = mGlobalOffset.y + (viewBound.left.y + (viewBound.right.y - checkboxPaddingEnd - viewBound.left.y) / 2);
	RECT rc = { textRenderPosition.x,centerY - textSize.y/2, textRenderPosition.x + textSize.x, centerY+textSize.y/2 };
	renderer->drawText(this->label,this->textColor, &rc);
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
	assert(widthSize == ViewSizeSpec::WRAP_CONTENT && heightSize == ViewSizeSpec::WRAP_CONTENT && "unsupported view spec");
	
	uintptr_t totalWidth = 0u;
	uintptr_t totalHeight = 0u;
	

	totalWidth += this->checkboxSize + checkboxPaddingEnd;
	totalHeight += this->checkboxSize + checkboxPaddingEnd;

	textSize = this->calcTextSize(this->label);

	totalWidth += this->textSize.x;
	totalHeight = max(totalHeight, textSize.y);


	setMeasuredDimension(min(availW, totalWidth), min(availH, totalHeight));
}

void CheckBoxView::onLayout()
{
	textPosition.x = viewBound.left.x + this->checkboxSize + checkboxPaddingEnd;
	textPosition.y = viewBound.left.y;
}
