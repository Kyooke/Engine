#pragma once

class Graphics;

class Image
{
public:

    static void Initialize(Graphics* graphics);

    static int Load(const char* fileName);

    static void Release(int handle);

    static void Set(int handle);

private:

    static Graphics* graphics_;
};