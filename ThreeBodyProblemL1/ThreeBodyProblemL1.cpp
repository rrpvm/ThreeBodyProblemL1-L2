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
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_PAINT:

        return 0;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}
constexpr int waitTime = 1000 / 120;
void scene1(Window* window);
int WindowApplication(HINSTANCE hInstance, int nCmdShow) {
    const char* CLASS_NAME = "RRPVM_CLASS_NAME";

    // Регистрация класса окна
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Создание окна
    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        "Three body problem solve",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720,
        NULL, NULL, hInstance, NULL
    );

    if (!hwnd) return 0;

    ShowWindow(hwnd, nCmdShow);

    // Цикл обработки сообщений
    MSG msg = {};
    HDC windowDeviceContext = GetDC(hwnd);
    IRender* renderer = new  WinGdiRender(windowDeviceContext);
    Window solveWindow = Window(1280, 720, { 255,255,255,255 });
    scene1(&solveWindow);
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        renderer->drawWindow(solveWindow);
        
        std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));
    }
    delete renderer;
    return 0;
}
void scene1(Window* window) {
    LinearLayout* mGuiRoot = new LinearLayout("mainRoot", LinearLayoutOrientation::VERTICAL, ViewSizeSpec::MATCH_PARENT, ViewSizeSpec::WRAP_CONTENT);
    mGuiRoot->setBackgroundColor(new Color(255, 33, 33, 33));
    CheckBoxView* cbv1 = new CheckBoxView("first checkbox", 40,40);
    CheckBoxView* cbv2 = new CheckBoxView("second checkbox", 40,40);
    LinearLayout* secondRoot = new LinearLayout("secondRoot", LinearLayoutOrientation::VERTICAL, ViewSizeSpec::MATCH_PARENT, ViewSizeSpec::WRAP_CONTENT);
    secondRoot->setBackgroundColor(new Color(255, 99, 99, 99));
    CheckBoxView* cbv3 = new CheckBoxView("third checkbox", 40, 40);


    mGuiRoot->addView(new SpacerView("spacerView", 0, 80));
    mGuiRoot->addView(cbv1);
    mGuiRoot->addView(cbv2);
    secondRoot->addView(new SpacerView("spacerView", 0, 50));
    secondRoot->addView(cbv3);
    mGuiRoot->addView(secondRoot);
    window->setView(mGuiRoot);
}

int main()
{
    setlocale(LC_ALL, "ru");
    std::cout << "Запускаем чертолёт!";
    return WindowApplication(GetModuleHandle(NULL), SW_SHOW);
}
