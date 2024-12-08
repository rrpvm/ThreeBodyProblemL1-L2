#include "LinearLayout.hpp"
#include "IRender.h"
#include <math.h>
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

	if (mBackgroundColor != nullptr) {
		renderer->drawFilledRect(*mBackgroundColor, this->viewBound.left + mGlobalOffset, {(int)this->mViewLayoutParams->width,(int)this->mViewLayoutParams->height});
	}
	for (const auto& view : mViews) {
		if (view == nullptr)continue;
		view->draw(renderer);
	}
}

void LinearLayout::onAttachedToWindow(Window* mWindow)
{
	attachedWindowSize = mWindow->getSize();
	if (this->mParentView == nullptr) {
		for (const auto& view : mViews) {
			view->onAttachedToWindow(mWindow);
		}
		setBoundRect({ 0,0,attachedWindowSize.x,attachedWindowSize.y });
		requestLayout();
	
	}
}

void LinearLayout::onMeasure()
{
	uintptr_t totalWidth = 0;
	uintptr_t totalHeight = 0;
	
	uintptr_t parentWidthSpec = (widthSize == ViewSizeSpec::HARD) ? measuredWidth: attachedWindowSize.x;
	uintptr_t parentHeightSpec = (heightSize == ViewSizeSpec::HARD) ? measuredHeight: attachedWindowSize.y;

	//первый проход: грубое взешивание
	for (const auto& child : mViews) {
		
		child->measure(parentWidthSpec, parentHeightSpec);

		if (mOrientation == VERTICAL) {
			totalHeight += child->measuredHeight; 
			totalWidth = max(totalWidth, child->measuredWidth); 
		}
		else if (mOrientation == HORIZONTAL) {
			totalWidth += child->measuredWidth;
			totalHeight = max(totalHeight, child->measuredHeight);
		}
	}
	if (widthSize == ViewSizeSpec::WRAP_CONTENT) {
		measuredWidth = totalWidth;
	}
	if (heightSize == ViewSizeSpec::WRAP_CONTENT) {
		measuredHeight = totalHeight;
	}
	//second iteration
	uintptr_t resultWidth = 0u;
	uintptr_t resultHeight = 0u;
	for (const auto& child : mViews) {
		uintptr_t childWidthSpec = (child->widthSize == ViewSizeSpec::MATCH_PARENT) ? parentWidthSpec : child->measuredWidth;
		uintptr_t childHeightSpec = (child->heightSize == ViewSizeSpec::MATCH_PARENT) ? parentHeightSpec : child->measuredHeight;
		child->measure(childWidthSpec, childHeightSpec);
		resultWidth = (mOrientation == VERTICAL) ? max(resultWidth, child->measuredWidth) : resultWidth + child->measuredWidth;
		resultHeight = (mOrientation == VERTICAL) ? resultHeight + child->measuredHeight : max(resultHeight, child->measuredHeight);
	}
	if (widthSize == ViewSizeSpec::MATCH_PARENT) {
		resultWidth = parentWidthSpec;
	}
	if (heightSize == ViewSizeSpec::MATCH_PARENT) {
		resultHeight = parentHeightSpec;
	}
	setMeasuredDimension(resultWidth, resultHeight);
}

void LinearLayout::measure(uintptr_t availW, uintptr_t availH)
{
	
	onMeasure();
}

void LinearLayout::onLayout()
{
	std::cout << "onLayout() \t " << (uintptr_t*)(this) << std::endl;
	BoundRect tmpBound = BoundRect(viewBound.left.x, viewBound.left.y,viewBound.right.x,viewBound.right.y);
	for (const auto& view : mViews) {
		if (view == nullptr)continue;
		int leftPosX = tmpBound.left.x;
		int leftPosY = tmpBound.left.y;
		int rightPosX = min(leftPosX + view->measuredWidth, viewBound.right.x);
		int rightPosY = min(leftPosY + view->measuredHeight, viewBound.right.y);
		tmpBound.right.x = rightPosX;
		tmpBound.right.y = rightPosY;
		view->setBoundRect(tmpBound);
		if (dynamic_cast<ParentView*>(view)) {
			view->onLayout();
		}
		tmpBound.left.x += 0;
		tmpBound.left.y += view->measuredHeight;
	}
}