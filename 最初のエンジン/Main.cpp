#include "Window.h"
#include "Graphics.h"
#include "Input.h"
#include "Timer.h"
#include "RootObject.h"
#include "SceneManager.h"


int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE,
    LPSTR,
    int)
{
    Window window;
    Graphics graphics;
    RootObject root;

    Timer::Initialize();

    if (!window.Initialize(
        hInstance,
        1280,
        720,
        L"Treasure Engine"))
    {
        return -1;
    }

    if (!graphics.Initialize(
        window.GetHwnd(),
        1280,
        720))
    {
        return -1;
    }


    while (window.ProcessMessage())
    {
        Timer::Update();
        Input::Update();

        graphics.BeginFrame();

        root.UpdateSub();

        root.DrawSub();

        graphics.EndFrame();
    }


    return 0;
}