#include "ApplicationState.h"
#include "IRenderStat.h"
#include "IRender.h"
#include "WinGdiRender.hpp"
void ApplicationState::addDefaultBody()
{
    bodyDataMutex.lock();
    static int id = 1337;
    auto body = new DefaultBody(id++, appState.applicationUniverse->getCmd());
    mBodies.push_back(body);
    appState.applicationUniverse->addBody(body);
    bodyDataMutex.unlock();
}
void ApplicationState::addCustomBody(DefaultBody* mBase)
{
    bodyDataMutex.lock();
    this->mBodies.push_back(mBase);
    appState.applicationUniverse->addBody(mBase);
    bodyDataMutex.unlock();
}
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
