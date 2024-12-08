#include "GuiState.hpp"

void GuiHelper::onWindowCreate(Window* window)
{
	mWindows.push_back(window);
}

std::vector<Window*> GuiHelper::getWindowsToRender()
{
	return mWindows;//пока забьем на видимость - рендерим все
}

void __stdcall defaultGuiProcessEvent(const MouseEvent& mEvent)
{
	for (Window* wnd : gui->getWindowsToRender()) {
		wnd->processMouseEvent(mEvent);
	}
}
