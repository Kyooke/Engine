#include "Camera.h"

using namespace DirectX;

Camera::Camera()
    : GameObject("Camera")
{

    transform_.position.z = -5.0f;
}

void Camera::Update()
{

}

XMMATRIX Camera::GetViewMatrix() const
{
    XMVECTOR eye =
        XMVectorSet(
            transform_.position.x,
            transform_.position.y,
            transform_.position.z,
            1.0f);

    XMVECTOR target =
        XMVectorSet(
            0.0f,
            0.0f,
            0.0f,
            1.0f);

    XMVECTOR up =
        XMVectorSet(
            0.0f,
            1.0f,
            0.0f,
            0.0f);

    return XMMatrixLookAtLH(
        eye,
        target,
        up);
}