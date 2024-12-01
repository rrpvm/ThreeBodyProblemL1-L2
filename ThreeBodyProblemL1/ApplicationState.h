#pragma once
#include <memory>
#include "Universe.h"

class ApplicationState {
public:
	HWND windowHWND;
	std::unique_ptr<Universe> applicationUniverse{ new Universe(10,6.67e-11) };
	std::unique_ptr<IRender> renderer;//late init
	
	
	
};
extern ApplicationState appState;