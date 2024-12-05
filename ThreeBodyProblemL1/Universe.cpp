#include "Universe.h"
#include <thread>
#include <chrono>
#define LOGIC_TARGET_FPS 185
constexpr uintptr_t LOGIC_TARGET_DELAY = 1000 / LOGIC_TARGET_FPS;
void Universe::addBody(DefaultBody* body)
{
	for (const DefaultBody* mBody : mBodies) {
		if (mBody == body)return;
	}
	mBodies.push_back(body);
}

void Universe::runSimulation()
{
	this->isRunning = true;
	mCmd.setBodies(mBodies);
	while (isRunning) {
		for (DefaultBody* body : mBodies) {
			body->update(mCmd.deltaTime);
		}
		mCmd.update(mCmd.currentTick);
		mCmd.currentTick++;
		this->mPreparedCallback();
		std::this_thread::sleep_for(std::chrono::milliseconds(LOGIC_TARGET_DELAY));
	}
}

void Universe::stopSimulation()
{
	isRunning = false;
}
