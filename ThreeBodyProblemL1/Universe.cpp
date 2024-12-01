#include "Universe.h"
#include <thread>
#include <chrono>
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
	while (isRunning) {
		if (mCmd.currentTick == 0) {
			mCmd.update(0, mBodies);
		}
		mCmd.currentTick++;
		for (const auto& body : mBodies) {
			body->update(mCmd.deltaTime);
		}
		mCmd.update(mCmd.currentTick, mBodies);
		this->mPreparedCallback();
		std::this_thread::sleep_for(std::chrono::microseconds(100));
	}
}

void Universe::stopSimulation()
{
	isRunning = false;
}
