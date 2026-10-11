#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

class Window
{
public:
    bool Initialize(
        HINSTANCE hInstance, // Application instance
        int width, // width
        int height, // height
        const wchar_t* title); // title
    bool ProcessMessage();

    HWND GetHwnd() const
    {
        return hwnd_;
    }

private:
    HWND hwnd_ = nullptr; // window handle
};