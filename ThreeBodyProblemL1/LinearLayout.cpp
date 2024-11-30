#include "LinearLayout.hpp"
#include "IRender.h"
void LinearLayout::addView(BaseView* mView)
{
	for (const auto& view : mViews) {
		if (view == mView)return;
	}
	mViews.push_back(mView);
	mView->onAttachedToView(this);
	if (mParentView != nullptr) {
		mParentView->requestLayout();
	}
	else {
		requestLayout();
	}

}
void LinearLayout::draw(IRender* renderer)
{
	/*if (mBackgroundColor != nullptr) {
		renderer->drawFilledRect(*mBackgroundColor, this->mBounds.left, {(int)this->mViewLayoutParams->width,(int)this->mViewLayoutParams->height});
	}
	for (const auto& view : mViews) {
		if (view == nullptr)continue;
		view->draw(renderer);
	}*/
}

void LinearLayout::onAttachedToWindow(Window* mWindow)
{
	requestLayout();
}

void LinearLayout::onMeasure()
{
	/*int measuredWidth = 0;
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
		for (const auto& view : mViews) {
			if (view == nullptr)continue;
			view->setBounds(this->mBounds);
			view->onMeasure();
			measuredHeight += view->measuredHeight;
		}
	}
	else {
		measuredHeight = this->mViewLayoutParams->height;
	}
	setMeasuredDimension(measuredWidth, measuredHeight);*/
}

void LinearLayout::measure(uintptr_t availW, uintptr_t availH)
{
}

void LinearLayout::onLayout()
{
	/*int offsetY = 0;
	BoundRect restRect = this->mBounds;
	for (const auto& view : mViews) {
		if (view == nullptr)continue;
		int leftPosX = restRect.left.x;
		int leftPosY = restRect.left.y + offsetY;
		int rightPosX = measuredWidth;
		int rightPosY = measuredHeight;
		if (dynamic_cast<ParentView*>(view)) {
			view->onLayout();
		}
		view->setBounds({ leftPosX,leftPosY,rightPosX ,rightPosY });
		offsetY += view->measuredHeight;
	}*/
}