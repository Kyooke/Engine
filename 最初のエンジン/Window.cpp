#include "Window.h"

LRESULT CALLBACK WindowProc(
    HWND hwnd,
    UINT msg,
    WPARAM wParam,
    LPARAM lParam)
{
    switch (msg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(
        hwnd,
        msg,
        wParam,
        lParam);
}

bool Window::Initialize(
    HINSTANCE hInstance,
    int width,
    int height,
    const wchar_t* title)
{
    const wchar_t CLASS_NAME[] =
        L"TreasureEngineWindow";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

	hwnd_ = CreateWindowEx(//windowを作る
        0,
        CLASS_NAME,
        title,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        width,
        height,
        nullptr,
        nullptr,
        hInstance,
        nullptr);

    if (hwnd_ == nullptr)
    {
        return false;
    }

	ShowWindow(hwnd_, SW_SHOW);//ウィンドウを表示する

    return true;
}
bool Window::ProcessMessage()//メッセージ処理
    {
        MSG msg = {};

        while (PeekMessage(
            &msg,
            nullptr,
            0,
            0,
            PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                return false;
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        return true;
    }