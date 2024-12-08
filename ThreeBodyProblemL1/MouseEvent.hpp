#pragma once
struct MouseEvent;
typedef void(__stdcall* onEventCallback)(const MouseEvent& event);
struct MouseEvent {
	int x{ 0 };
	int y{ 0 };
	int dx{ 0 }, dy{ 0 };
	bool isMouseClickedNow;
	bool isMouseButtonPressed;
	bool isMouseUnpressedNow;
	//bool isMouse
	MouseEvent() {

	};
	MouseEvent(const MouseEvent& event) {
		this->x = event.x;
		this->y = event.y;
		this->dx = event.dx;
		this->dy = event.dy;
		this->isMouseButtonPressed = event.isMouseButtonPressed;
		this->isMouseClickedNow = event.isMouseClickedNow;
		this->isMouseUnpressedNow = event.isMouseUnpressedNow;
	}
};