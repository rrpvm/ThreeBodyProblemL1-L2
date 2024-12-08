#pragma once
#include <wtypes.h>
#include <string>
#include "MouseEvent.hpp"
//mouse controller

class UserInputController {
private:
	onEventCallback onEventProceedCallback = nullptr;
	MouseEvent prevMouseEvent{};
public:
	void onMoveEvent(WPARAM wParam, LPARAM lParam);
	void onClickDownEvent();
	void onClickUpEvent();
	void setOnEventCallback(onEventCallback callback);
private:
	void onProceed(const MouseEvent& newEvent);
	std::string to_string() {
		return "mouse_x " + std::to_string(prevMouseEvent.x) + "; mouse_y " + std::to_string(prevMouseEvent.y)
			+ "; dx " + std::to_string(prevMouseEvent.dx) + "; dy " + std::to_string(prevMouseEvent.dy) +
			"; lkmPressed " + std::to_string(prevMouseEvent.isMouseButtonPressed);
	}
};