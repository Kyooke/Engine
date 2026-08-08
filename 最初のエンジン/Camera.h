#pragma once

#include "GameObject.h"

#include <DirectXMath.h>

class Camera : public GameObject
{
public:

    Camera();

    void Update() override;

    DirectX::XMMATRIX GetViewMatrix() const;
};