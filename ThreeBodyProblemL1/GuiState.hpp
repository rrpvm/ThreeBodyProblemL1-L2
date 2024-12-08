#pragma once
#include "Window.hpp"
#include <vector>
#include "MouseEvent.hpp"
class GuiHelper {
public:
	void onWindowCreate(Window* window);
	std::vector<Window*> getWindowsToRender(); 
private:
	std::vector<Window*> mWindows;//contract : Windows deletes only in gui helper
};
void __stdcall defaultGuiProcessEvent(const MouseEvent& mEvent);
inline std::unique_ptr<GuiHelper>gui(new GuiHelper());