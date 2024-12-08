#include "UserInputController.hpp"
#include <windowsx.h>
#include <iostream>

void UserInputController::onMoveEvent(WPARAM wParam, LPARAM lParam)
{
    bool isPressedLbutton = wParam & MK_LBUTTON;
    int xPos = GET_X_LPARAM(lParam);
    int yPos = GET_Y_LPARAM(lParam);

    MouseEvent currentMouseEvent = prevMouseEvent;

    currentMouseEvent.dx = xPos - prevMouseEvent.x;
    currentMouseEvent.dy = yPos - prevMouseEvent.y;

    currentMouseEvent.x = xPos;
    currentMouseEvent.y = yPos;
    currentMouseEvent.isMouseButtonPressed = isPressedLbutton;
    currentMouseEvent.isMouseClickedNow = false;
    currentMouseEvent.isMouseUnpressedNow = false;
    onProceed(currentMouseEvent);
}

void UserInputController::onClickDownEvent()
{
    MouseEvent currentMouseEvent = prevMouseEvent;
    currentMouseEvent.dx = 0;
    currentMouseEvent.dy = 0;
    currentMouseEvent.isMouseClickedNow = true;
    currentMouseEvent.isMouseButtonPressed = true;
    currentMouseEvent.isMouseUnpressedNow = false;
    onProceed(currentMouseEvent);
}

void UserInputController::onClickUpEvent()
{
    MouseEvent currentMouseEvent = prevMouseEvent;
    currentMouseEvent.dx = 0;
    currentMouseEvent.dy = 0;
    currentMouseEvent.isMouseClickedNow = false;
    currentMouseEvent.isMouseButtonPressed = false;
    currentMouseEvent.isMouseUnpressedNow = true;
    onProceed(currentMouseEvent);
}

void UserInputController::setOnEventCallback(onEventCallback callback)
{
    this->onEventProceedCallback = callback;
}

void UserInputController::onProceed(const MouseEvent& newEvent)
{
    this->prevMouseEvent = newEvent;
   // std::cout << this->to_string() << std::endl;
    if (onEventProceedCallback != nullptr) {
        onEventProceedCallback(newEvent);
    }
}

