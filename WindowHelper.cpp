#include "WindowHelper.h"
#include <iostream>

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) 
{
    switch (message) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        break;
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}

bool SetupWindow(HINSTANCE instance, UINT width, UINT height, int nCmdShow, HWND& wnd)
{
    const wchar_t CLASS_NAME[] = L"class name";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = instance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    wnd = CreateWindowEx(0, CLASS_NAME, L"01100001 01101110 00100000 01100101 01100111 01100111 ", WS_OVERLAPPEDWINDOW, 0, 0, width, height, nullptr, nullptr, instance, nullptr);

    if (wnd == nullptr) {
        std::cerr << "cant create window" << std::endl;
        return false;
    }

    ShowWindow(wnd, nCmdShow);

    return true;
}
