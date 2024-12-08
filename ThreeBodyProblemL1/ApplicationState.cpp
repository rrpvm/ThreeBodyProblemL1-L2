#include "ApplicationState.h"
#include "IRenderStat.h"
#include "IRender.h"
#include "WinGdiRender.hpp"
void ApplicationState::applyConfig()
{
    IRender* mRender = renderer.get();
    IRenderStat* renderStat = dynamic_cast<IRenderStat*>(mRender);
    if (renderStat != nullptr) {
        if (appConfig.showFPS) {
            renderStat->startShowFPS(FpsPosition::TOP_RIGHT);
        }
        else renderStat->stopShowFPS();
        this->applicationUniverse->setPausedSimulating(appConfig.pauseUniverse);
    }
}
