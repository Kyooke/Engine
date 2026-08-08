#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

class Window
{
public:
    bool Initialize(
        HINSTANCE hInstance,//今動いているアプリ
        int width,//横
		int height,//縦
		const wchar_t* title);//タイトル
    bool ProcessMessage();

    HWND GetHwnd() const
    {
        return hwnd_;
    }

private:
	HWND hwnd_ = nullptr;//ウィンドウの番号
};