#pragma once
#include <memory>
#include <vector>
#include <Windows.h>
#include "Universe.h"
#include "UserInputController.hpp"
class ApplicationState {
private:
	const double APPLICATION_DT = 0.01;
	const double APPLICATION_GRAVITY_CONST = 0.0001;
public:
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

};
extern ApplicationState appState;