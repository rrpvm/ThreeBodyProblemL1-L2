#pragma once
#include <memory>
#include <vector>
#include <mutex>
#include <Windows.h>
#include "Universe.h"
#include "UserInputController.hpp"
#include "ApplicationConfig.hpp"

//anti-pattern god object. bye-bye SOLID - SRP (время дороже)
class ApplicationState {
private:
	const double APPLICATION_DT = 0.01;
	const double APPLICATION_GRAVITY_CONST = 0.0001;
	ApplicationConfig appConfig;
	
public:
	std::mutex bodyDataMutex;
	UserInputController* userInput = new UserInputController();
	const uintptr_t START_BODIES_COUNT = 16;
	ApplicationState() {
		srand(GetTickCount64());
	}
	~ApplicationState() {
		for (auto body : mBodies) {
			delete body;
		}
		mBodies.clear();
		delete userInput;
	}
	HWND windowHWND;
	std::unique_ptr<Universe> applicationUniverse{ new Universe(APPLICATION_DT,APPLICATION_GRAVITY_CONST) };
	std::unique_ptr<IRender> renderer;//late init
	std::vector<DefaultBody*> mBodies;
	void addDefaultBody();
	void addCustomBody(DefaultBody* mBase);
	bool isShowTickEnabled() {
		return this->appConfig.showTicks;
	}
	bool isShowEpochEnabled() {
		return this->appConfig.showEpochTime;
	}
	void onFpsConfigChange(bool arg) {
		this->appConfig.showFPS = arg;
		applyConfig();
	}
	void onPauseUniverseConfigChange(bool arg){
		this->appConfig.pauseUniverse = arg;
		applyConfig();
	}
	void onShowTicksChange(bool arg) {
		this->appConfig.showTicks = arg;
		applyConfig();
	}
	void onShowEpochChange(bool arg) {
		this->appConfig.showEpochTime = arg;
		applyConfig();
	}
private:
	void applyConfig();
};
extern ApplicationState appState;