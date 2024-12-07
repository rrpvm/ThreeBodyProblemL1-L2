#pragma once
#include "Vector2.hpp"
enum class FpsPosition {
	START, END, TOP_RIGHT, BOT_LEFT
};
class IRenderStat {
public:
	virtual ~IRenderStat() {

	}
	virtual void startShowFPS(FpsPosition position) = 0;
	void stopShowFPS() {
		isShowFramesPerSecond = false;
	}
	uintptr_t getFPS() {
		return fps;
	}
protected:
	ULONGLONG lastCalcFrom = 0;
	bool isShowFramesPerSecond = false;
	uintptr_t fps{ 0 };
	uintptr_t calcedFps{ 0 };
};