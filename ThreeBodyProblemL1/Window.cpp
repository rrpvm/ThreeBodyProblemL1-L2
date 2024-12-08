#include "Window.hpp"
#include "IRender.h"
#include "GuiState.hpp"
#include "Utils.hpp"
Window::Window(uintptr_t _width, uintptr_t _height, Color backgroundColor)
{
	this->mWidth = _width;
	this->mHeight = _height;
	this->mBackgroundColor = backgroundColor;
	this->size = { static_cast<int>(_width),static_cast<int>(_height) };
	gui->onWindowCreate(this);
}
void Window::setView(ParentView* mView)
{
	this->mParentView = mView;
	mView->onAttachedToWindow(this);
	mView->setBoundRect(BoundRect(this->origin.x, this->origin.y, this->size.x, this->size.y));
}

void Window::processMouseEvent(const MouseEvent& mouseEvent)
{
	if (!Utils::isPointInBB({ mouseEvent.x,mouseEvent.y }, origin, size)) {
		isDragging = false;
		return;
	}
	if (mouseEvent.isMouseClickedNow) {
		isDragging = true;
		this->timeStartDragging = GetTickCount();
	}
	if (mouseEvent.isMouseUnpressedNow) {
		isDragging = false;
	}
	if (isDragging && (mouseEvent.dx != 0 || mouseEvent.dy != 0) && mouseEvent.isMouseButtonPressed) {
		this->setOrigin({ origin.x + mouseEvent.dx, origin.y + mouseEvent.dy });
	}
	else {

	}
}

void Window::draw(IRender* renderer)
{
	assert(this->mParentView != nullptr && "did you attach the view to window?");
	renderer->drawFilledRect(this->mBackgroundColor, this->origin, this->size);
	renderer->drawRect(BLACK, this->origin, this->size,2);
	if (mParentView == nullptr)return;
	mParentView->draw(renderer);
}

