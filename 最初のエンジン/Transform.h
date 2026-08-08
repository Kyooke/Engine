#pragma once

#include "Vector3.h"

#include <DirectXMath.h>

class Transform
{
public:

    Vector3 position;
    Vector3 rotation;
    Vector3 scale;

    Transform();

    DirectX::XMMATRIX GetWorldMatrix() const;
};