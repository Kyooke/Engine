#include "Timer.h"
#include <Windows.h>


float Timer::deltaTime_ = 0.0f;

unsigned long long Timer::oldTime_ = 0;

void Timer::Initialize()
{
    oldTime_ = GetTickCount64();
}

void Timer::Update()
{
    unsigned long long nowTime =
        GetTickCount64();


    deltaTime_ =
        (nowTime - oldTime_) / 1000.0f;


    oldTime_ = nowTime;
}

float Timer::DeltaTime()
{
    return deltaTime_;
}

