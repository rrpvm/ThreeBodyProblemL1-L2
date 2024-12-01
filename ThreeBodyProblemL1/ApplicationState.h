#pragma once
#include <memory>
#include "Universe.h"

class ApplicationState {
public:
	HWND windowHWND;
	std::unique_ptr<Universe> applicationUniverse{ new Universe(0.1) };
	std::unique_ptr<IRender> renderer;//late init
	
	
	
};
extern ApplicationState appState;