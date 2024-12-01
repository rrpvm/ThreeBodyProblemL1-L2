#include "Window.hpp"
#include "IRender.h"
void Window::setView(ParentView* mView)
{
	this->mParentView = mView;
	mView->onAttachedToWindow(this);
}

void Window::draw(IRender* renderer)
{
	renderer->drawFilledRect(this->mBackgroundColor, this->origin, this->size);
	if (mParentView == nullptr)return;
	mParentView->draw(renderer);
}
