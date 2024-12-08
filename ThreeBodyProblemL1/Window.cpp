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
	this->mRootView = mView;
	mView->setBoundRect(BoundRect(this->origin.x, this->origin.y, this->size.x, this->size.y));
	mView->onAttachedToWindow(this);
}

void Window::processMouseEvent(const MouseEvent& mouseEvent)
{
	if (!Utils::isPointInBB({ mouseEvent.x,mouseEvent.y }, origin, size)) {
		isDragging = false;
		mRootView->dispatchMouseEvent(mouseEvent);
		return;
	}
	if (mouseEvent.isMouseClickedNow) {
		isDragging = true;
		this->timeStartDragging = GetTickCount();
	}
	if (mouseEvent.isMouseUnpressedNow) {
		isDragging = false;
	}
	if (isDragging && (mouseEvent.dx != 0 || mouseEvent.dy != 0) && mouseEvent.isMouseButtonPressed && GetTickCount() > timeStartDragging + 100) {
		this->setOrigin({ origin.x + mouseEvent.dx, origin.y + mouseEvent.dy });
	}
	else {
		mRootView->dispatchMouseEvent(mouseEvent);
	}
}

void Window::draw(IRender* renderer)
{
	assert(this->mRootView != nullptr && "did you attach the view to window?");
	static const int extension = 3;
	static const int windowThickness = 3;
	static const Vector2 leftSub = Vector2(extension + windowThickness, extension +windowThickness);
	static const Vector2 rightSub = Vector2((extension + windowThickness) * 2, (extension + windowThickness) * 2);
	static Color borderOuterColor = Color(255, 11, 11, 11);
	static Color borderInnerColor = Color(255, 44, 44, 44);
	renderer->drawFilledRect(this->mBackgroundColor, this->origin, this->size);
	renderer->drawRect(borderOuterColor, this->origin - leftSub, this->size + rightSub, windowThickness);
	renderer->drawRect(borderInnerColor, this->origin, this->size, windowThickness);
	if (mRootView == nullptr)return;
	mRootView->draw(renderer);
}

