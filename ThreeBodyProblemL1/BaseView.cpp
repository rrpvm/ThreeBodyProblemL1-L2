#include "BaseView.h"

void BaseView::setBackgroundColor(const Color* mColor)
{
	if (mBackgroundColor != nullptr) {
		delete mBackgroundColor;
		mBackgroundColor = nullptr;
	}
	this->mBackgroundColor = new Color(*mColor);
}

void BaseView::requestLayout()
{
	onMeasure();
	onLayout();
}

