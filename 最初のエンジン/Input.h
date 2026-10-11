#pragma once

#include <Windows.h>

class Input
{
public:

    static void Update();

    // While key is held down
    static bool IsKeyDown(int key);

    // Key pressed (edge)
    static bool IsKey(int key);

    // Key released (edge)
    static bool IsKeyUp(int key);

private:

    static SHORT key_[256];

    // Previous key state
    static SHORT oldKey_[256];
};