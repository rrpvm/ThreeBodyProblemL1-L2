#include "BaseView.h"

void BaseView::setBackgroundColor(Color* mColor)
{
	this->mBackgroundColor = mColor;
}

void BaseView::requestLayout()
{
	measuredWidth = 0;
	measuredHeight = 0;

	onMeasure();
	onLayout();
}

