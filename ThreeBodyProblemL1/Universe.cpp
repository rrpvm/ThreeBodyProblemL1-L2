#include "Universe.h"
#include <thread>
#include <chrono>
#define LOGIC_TARGET_FPS 240
constexpr uintptr_t LOGIC_TARGET_DELAY = 1000000 / LOGIC_TARGET_FPS;
void Universe::addBody(DefaultBody* body)
{
	for (const DefaultBody* mBody : mBodies) {
		if (mBody == body)return;
	}
	mBodies.push_back(body);
	mCmd.setBodies(mBodies);
}

void Universe::runSimulation()
{
	this->isRunning = true;
	while (isRunning) {
		if (isPauseSimulating) {
			this->mPreparedCallback();
			std::this_thread::sleep_for(std::chrono::microseconds(LOGIC_TARGET_DELAY));
			continue;
		}
		for (DefaultBody* body : mBodies) {
			body->update(mCmd.deltaTime);
		}
		mCmd.update(mCmd.currentTick);
		mCmd.currentTick++;
		this->mPreparedCallback();
		std::this_thread::sleep_for(std::chrono::microseconds(LOGIC_TARGET_DELAY));
	}
}

void Universe::stopSimulation()
{
	isRunning = false;
}

void Universe::setPausedSimulating(bool simulation)
{
	this->isPauseSimulating = simulation;
}
