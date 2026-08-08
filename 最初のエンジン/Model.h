#pragma once

#include "Transform.h"

class Graphics;
class Mesh;

class Model
{
public:

    static void Initialize(Graphics* graphics);

    static int Load(const char* fileName);

    static void Release(int handle);

    static void SetTransform(int handle,const Transform& transform);

    static void SetTexture(int handle, int textureHandle);

    static void Draw(int handle);


private:

    static Graphics* graphics_;
};