#pragma once

class Timer
{
public:

    //開始時に呼ぶ
    static void Initialize();
    //毎フレーム呼ぶ
    static void Update();
    //前回から経過した時間(秒)
    static float DeltaTime();
private:

    //前回更新からの時間
    static float deltaTime_;


    //前回の時間
    static unsigned long long oldTime_;
};