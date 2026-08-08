#include "Transform.h"

using namespace DirectX;

Transform::Transform()
{
    position = Vector3(0.0f, 0.0f, 0.0f);
    rotation = Vector3(0.0f, 0.0f, 0.0f);
    scale = Vector3(1.0f, 1.0f, 1.0f);
}

XMMATRIX Transform::GetWorldMatrix() const
{
    XMMATRIX scaleMatrix =
        XMMatrixScaling(
            scale.x,
            scale.y,
            scale.z);

    XMMATRIX rotationMatrix =
        XMMatrixRotationRollPitchYaw(
            XMConvertToRadians(rotation.x),
            XMConvertToRadians(rotation.y),
            XMConvertToRadians(rotation.z));

    XMMATRIX translationMatrix =
        XMMatrixTranslation(
            position.x,
            position.y,
            position.z);

    return
        scaleMatrix *
        rotationMatrix *
        translationMatrix;
}