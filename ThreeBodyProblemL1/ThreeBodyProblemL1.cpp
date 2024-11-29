#include <iostream>
#include <Windows.h>
#include "WinGdiRender.hpp"
#include "Vector2.hpp"
#include "Color.h"
#include "Window.hpp"
#include "LinearLayout.hpp"
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
int WindowApplication(HINSTANCE hInstance, int nCmdShow) {
    const char* CLASS_NAME = "SampleWindowClass";

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
        "My Window",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL, hInstance, NULL
    );

    if (!hwnd) return 0;

    ShowWindow(hwnd, nCmdShow);

    // Цикл обработки сообщений
    MSG msg = {};
    HDC windowDeviceContext =  GetDC(hwnd);
    IRender* renderer = new  WinGdiRender(windowDeviceContext);
    Window solveWindow = Window(640,480,{255,255,255,255});
    LinearLayout* mGuiRoot = new LinearLayout(LinearLayoutOrientation::VERTICAL,ViewSizeSpec::MATCH_PARENT,140);
    mGuiRoot->setBackgroundColor(new Color(255, 0, 255, 0));
    mGuiRoot->requestLayout();
    solveWindow.setView(mGuiRoot);
    renderer->drawWindow(solveWindow);
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    delete renderer;
    return 0;
}

int main()
{
    setlocale(LC_ALL, "ru");
    std::cout << "Запускаем чертолёт!";
    return WindowApplication(GetModuleHandle(NULL), SW_SHOW);
}
