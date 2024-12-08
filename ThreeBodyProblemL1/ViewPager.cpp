#include "ViewPager.hpp"

void ViewPager::showViewIndex(int index)
{
	this->selectViewIndex = index;
	onLayout();
}

void ViewPager::onMeasure()
{
	uintptr_t totalWidth = 0;
	uintptr_t totalHeight = 0;

	uintptr_t parentWidthSpec = (widthSize == ViewSizeSpec::HARD) ? measuredWidth : attachedWindowSize.x;
	uintptr_t parentHeightSpec = (heightSize == ViewSizeSpec::HARD) ? measuredHeight : attachedWindowSize.y;

	//первый проход: грубое взешивание
	for (const auto& child : mViews) {

		child->measure(parentWidthSpec, parentHeightSpec);
		totalWidth += child->measuredWidth;
		totalHeight = max(totalHeight, child->measuredHeight);
	}
	//second iteration
	uintptr_t resultWidth = 0u;
	uintptr_t resultHeight = 0u;
	auto weightViewsWidth = parentWidthSpec;
	for (const auto& child : mViews) {
		if (child->widthSize != ViewSizeSpec::MATCH_PARENT)continue;
		uintptr_t childWidthSpec = weightViewsWidth;
		uintptr_t childHeightSpec = (child->heightSize == ViewSizeSpec::MATCH_PARENT) ? parentHeightSpec : child->measuredHeight;
		child->measure(childWidthSpec, childHeightSpec);
		resultWidth = resultWidth + child->measuredWidth;
		resultHeight = max(resultHeight, child->measuredHeight);
	}
	if (widthSize == ViewSizeSpec::MATCH_PARENT) {
		resultWidth = parentWidthSpec;
	}
	if (heightSize == ViewSizeSpec::MATCH_PARENT) {
		resultHeight = parentHeightSpec;
	}
	setMeasuredDimension(resultWidth, resultHeight);
}

void ViewPager::onLayout()
{
	int i = 0;
	for (const auto& view : mViews) {
		if (view == nullptr) {
			i++;
			continue;
		}
		if (i != this->selectViewIndex) {
			view->setBoundRect({-1,-1,-1,-1});
			if (dynamic_cast<ParentView*>(view)) {
				view->onLayout();
			}
		}
		else {
			view->setBoundRect(viewBound);
			if (dynamic_cast<ParentView*>(view)) {
				view->onLayout();
			}
		}
		i++;
	}
}
