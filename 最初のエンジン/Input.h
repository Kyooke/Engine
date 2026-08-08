#pragma once

#include <Windows.h>

class Input
{
public:

    static void Update();

    //押している間
    static bool IsKeyDown(int key);

    //押した瞬間
    static bool IsKey(int key);

    //離した瞬間
    static bool IsKeyUp(int key);

private:

    static SHORT key_[256];

    //前回のキー状態
    static SHORT oldKey_[256];
};