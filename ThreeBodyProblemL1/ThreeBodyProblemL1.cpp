#include <iostream>
#include <Windows.h>
#include "WinGdiRender.hpp"
#include "Vector2.hpp"
#include "Color.h"
#include "Window.hpp"
#include "LinearLayout.hpp"
#include <thread>
#include <chrono>
#include "CheckBoxView.hpp"
#include "SpacerView.hpp"
#include "ApplicationState.h"
#include "EarthBody.hpp"
#include "SunBody.hpp"
#include "IRenderStat.h"
#include "UserInputController.hpp"
#include "GuiState.hpp"
#include "OutlinedButtonView.hpp"
#include "SelectableButton.hpp"
#include "ViewPager.hpp"

#define WND_NAME "Three body problem solve"
ApplicationState appState = ApplicationState();

void scene1(Window* window);
void onTBPCallback();
void threeBodyProblem();
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WindowApplication(HINSTANCE hInstance, int nCmdShow) {
    const char* CLASS_NAME = "RRPVM_CLASS_NAME";

    // Регистрация класса окна
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Создание окна
    appState.windowHWND = CreateWindowEx(
        0,
        CLASS_NAME,
        WND_NAME,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720,
        NULL, NULL, hInstance, NULL
    );

    if (!appState.windowHWND) return 0;
    Window* guiWindow = new Window(640, 480, { 255,255,255,255 });
    scene1(guiWindow);
    threeBodyProblem();
    ShowWindow(appState.windowHWND, nCmdShow);
    MSG msg = {};
    // Цикл обработки сообщений
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    appState.applicationUniverse->stopSimulation();
    delete guiWindow;
    //  simulationWorker.join();
    return 0;
}

int main()
{
    setlocale(LC_ALL, "ru");
    ApplicationState appState = ApplicationState();
    std::cout << "Запускаем чертолёт!";
    return WindowApplication(GetModuleHandle(NULL), SW_SHOW);
}
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_SIZE:
    {
        int width = LOWORD(lParam);
        int height = HIWORD(lParam);
        if (appState.renderer != nullptr) {
            appState.renderer->setScreenSize({ width,height });
        }
        break;
    }
    case WM_MOUSEMOVE:
    {
        appState.userInput->onMoveEvent(wParam, lParam);
        break;
    }
    case WM_LBUTTONDOWN:
    {
        appState.userInput->onClickDownEvent();
        break;
    }
    case WM_LBUTTONUP:
    {
        appState.userInput->onClickUpEvent();
        break;
    }
    case WM_CREATE:
    {
        HDC windowDeviceContext = GetDC(hwnd);
        appState.renderer = std::make_unique<WinGdiRender>(windowDeviceContext);
        appState.renderer->setScreenSize({ 1280,720 });
        appState.renderer->setBgColor(Color(255, 33, 33, 33));
        if (dynamic_cast<IRenderStat*>(appState.renderer.get())) {
            dynamic_cast<IRenderStat*>(appState.renderer.get())->startShowFPS(FpsPosition::TOP_RIGHT);
        }
        appState.userInput->setOnEventCallback((onEventCallback)defaultGuiProcessEvent);
        break;
    }
    case WM_PAINT: {
        appState.renderer->onFrame();
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

void scene1(Window* window) {
    window->setBgColor(Color(255, 77, 77, 77));
    LinearLayout* mGuiRoot = new LinearLayout("mainRoot", LinearLayoutOrientation::VERTICAL, ViewSizeSpec::MATCH_PARENT, ViewSizeSpec::MATCH_PARENT);
    int selectedTab = 0;

    mGuiRoot->setBackgroundColor(new Color(255, 77, 77, 77));//мы фартовые ребята
    {
        //top padding
        mGuiRoot->addView(new SpacerView("#topPadding",0,8));
    }
    {
        //container
        ViewPager* vp = new ViewPager("viewpager", ViewSizeSpec::MATCH_PARENT, ViewSizeSpec::MATCH_PARENT);
        vp->setBackgroundColor(new Color(255, 255, 0, 0));
        //tabs
        int paddingHorizontal = 8;
        LinearLayout* mTabsHeader = new LinearLayout("tabs", LinearLayoutOrientation::HORIZONTAL, ViewSizeSpec::MATCH_PARENT, ViewSizeSpec::WRAP_CONTENT);
        SelectableButton* mControlBtn = new SelectableButton("managementTab", "Управление", 2u, Color(255, 11, 11, 11), Color(255, 44, 44, 44), Color(255, 33, 33, 33), ViewSizeSpec::MATCH_PARENT, ViewSizeSpec::WRAP_CONTENT);
        SpacerView* spacerBtwTab = new SpacerView("#fff", 24, 0);
        SelectableButton* mSettingsBtn = new SelectableButton("settingsTab", "Настройки", 2u, Color(255, 11, 11, 11), Color(255, 44, 44, 44), Color(255, 33, 33, 33), ViewSizeSpec::MATCH_PARENT, ViewSizeSpec::WRAP_CONTENT);

        auto tabResolver = [](int* selectedTab, SelectableButton* mControlBtn, SelectableButton* mSettingsBtn,ViewPager* pager) {
            if (mControlBtn) mControlBtn->setSelected(*selectedTab == 0);
            if (mSettingsBtn) mSettingsBtn->setSelected(*selectedTab == 1);
            if (pager != nullptr) {
                pager->showViewIndex(*selectedTab);
            }
        };

        mControlBtn->setOnClickListener(new OnClickListener([&selectedTab, mControlBtn, mSettingsBtn,vp, tabResolver]() {
            selectedTab = 0;
            tabResolver(&selectedTab, mControlBtn, mSettingsBtn,vp);
            }));

        mSettingsBtn->setOnClickListener(new OnClickListener([&selectedTab, mControlBtn, mSettingsBtn, vp, tabResolver]() {
            selectedTab = 1;
            tabResolver(&selectedTab, mControlBtn, mSettingsBtn,vp);
            }));
        tabResolver(&selectedTab, mControlBtn, mSettingsBtn,vp);
        mTabsHeader->addView(new SpacerView("#leftSpacerTab", paddingHorizontal, 0));
        mTabsHeader->addView(mControlBtn);
        mTabsHeader->addView(spacerBtwTab);
        mTabsHeader->addView(mSettingsBtn);
        mTabsHeader->addView(new SpacerView("#rightSpacerTab", paddingHorizontal, 0));
        mGuiRoot->addView(mTabsHeader);
     
       

        LinearLayout* fragmentManagement = new LinearLayout("fragment1", LinearLayoutOrientation::VERTICAL, ViewSizeSpec::MATCH_PARENT, ViewSizeSpec::MATCH_PARENT);
        fragmentManagement->setBackgroundColor(new Color(255, 0, 255, 0));
        LinearLayout* fragmentSettigs = new LinearLayout("fragment2", LinearLayoutOrientation::VERTICAL, ViewSizeSpec::MATCH_PARENT, ViewSizeSpec::MATCH_PARENT);
        fragmentSettigs->setBackgroundColor(new Color(255, 255, 0, 255));

        vp->addView(fragmentManagement);
        vp->addView(fragmentSettigs);
        mGuiRoot->addView(vp);
    }
   
    
   
  
    window->setView(mGuiRoot);
}
void onTBPCallback() {
    IRender* renderer = appState.renderer.get();
    renderer->startFrame();
    renderer->clear();
    for (DefaultBody* fBody : appState.mBodies) {
        fBody->draw(appState.renderer.get());
    }
    static RECT tickRect = { 15,0,80,150 };
    static RECT timeRect = { 15,30,180,150 };
    std::string tickText = "tick: " + std::to_string(appState.applicationUniverse->getCmd()->currentTick);
    std::string timeText = "time: " + std::to_string(appState.applicationUniverse->getCmd()->currentTick * appState.applicationUniverse->getCmd()->deltaTime) + " seconds";
    renderer->drawText(tickText, &tickRect);
    renderer->drawText(timeText, &timeRect);

    for (Window* window : gui->getWindowsToRender()) {
        renderer->drawWindow(*window);
    }
    renderer->endFrame();
    InvalidateRect(appState.windowHWND, NULL, true);
};
void threeBodyProblem() {
   
    appState.applicationUniverse->setOnReadyFrameSimulation((UniversePreparedCallback)onTBPCallback);
    auto sun = new SunBody(Vector3D(), Vector3D(0.0F,-0.1F,.0F), appState.applicationUniverse->getCmd());
    auto earth = new EarthBody(appState.applicationUniverse->getCmd(), sun, Vector3D(13.0F,13.0F, 0.0F));
    appState.mBodies.push_back(sun);
    appState.mBodies.push_back(earth);
    for (int i = 0; i < appState.START_BODIES_COUNT; i++) {
        appState.mBodies.push_back(new DefaultBody(1337 + i, appState.applicationUniverse->getCmd()));
    }
    for (auto* b : appState.mBodies) {
        appState.applicationUniverse->addBody(b);
    }
    std::thread simulationWorker([] {
        appState.applicationUniverse->runSimulation();
        });
    simulationWorker.detach();
   
}