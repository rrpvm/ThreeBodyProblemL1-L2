#include "LinearLayout.hpp"
#include "IRender.h"
void LinearLayout::draw(IRender* renderer)
{
	if (mBackgroundColor != nullptr) {
		renderer->drawFilledRect(*mBackgroundColor, this->mBounds.left, {(int)this->mViewLayoutParams->width,(int)this->mViewLayoutParams->height});
	}
}

void LinearLayout::onAttachedToWindow(Window* mWindow)
{
	onMeasure();
}

void LinearLayout::onMeasure()
{
	int measuredWidth = 0;
	int measuredHeight = 0;
	if (this->widthSize == ViewSizeSpec::MATCH_PARENT) {
		measuredWidth = this->mBounds.right.x;
	}
	else if (this->widthSize == ViewSizeSpec::WRAP_CONTENT) {
		measuredWidth = 250;
	}
	else {
		measuredWidth = this->mViewLayoutParams->width;
	}
	if (this->heightSize == ViewSizeSpec::MATCH_PARENT) {
		measuredHeight = this->mBounds.right.x;
	}
	else if (this->heightSize == ViewSizeSpec::WRAP_CONTENT) {
		measuredHeight = 250;
	}
	else {
		measuredHeight = this->mViewLayoutParams->height;
	}
	setMeasuredDimension(measuredWidth, measuredHeight);
}

void LinearLayout::onLayout()
{

}
