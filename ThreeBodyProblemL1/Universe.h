#pragma once
#include "UniverseCmd.hpp"
#include <functional>
typedef void(__stdcall* UniversePreparedCallback)();
class Universe {
private:
	double universeLifetime{ 0.0 };
	bool isRunning{ false };
	std::vector<DefaultBody*> mBodies;
	UniverseCmd mCmd;
	UniversePreparedCallback mPreparedCallback = nullptr;
public:
	
	Universe(double dt = 0.1, double G = 6.67e-3): mCmd(UniverseCmd(dt,G)) {};
	~Universe() {}
	void addBody(DefaultBody* body);
	void runSimulation();
	void stopSimulation();
	void setOnReadyFrameSimulation(UniversePreparedCallback callback) {
		mPreparedCallback = callback;
	}
	UniverseCmd* getCmd() {
		return &mCmd;
	}
};