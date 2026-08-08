#include "Input.h"


SHORT Input::key_[256] = {};
SHORT Input::oldKey_[256] = {};

void Input::Update()
{
    for (int i = 0; i < 256; i++)
    {
        oldKey_[i] = key_[i];

        key_[i] = GetAsyncKeyState(i);
    }
}

bool Input::IsKeyDown(int key)
{
    return (key_[key] & 0x8000);
}

bool Input::IsKey(int key)
{
    return
        (key_[key] & 0x8000) &&
        !(oldKey_[key] & 0x8000);
}

bool Input::IsKeyUp(int key)
{
    return
        !(key_[key] & 0x8000) &&
        (oldKey_[key] & 0x8000);
}