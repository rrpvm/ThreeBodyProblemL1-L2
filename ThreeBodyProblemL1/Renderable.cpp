#include "Renderable.h"
#include "ApplicationState.h"
#include "IRender.h"
 Vector2 IRenderable::calcTextSize(const char* text)
{
	return appState.renderer->getTextSize(text);
}
