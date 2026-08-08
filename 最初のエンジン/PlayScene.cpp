#include "PlayScene.h"
#include <Windows.h>

PlayScene::PlayScene()
    : Scene("PlayScene")
{
}

PlayScene::~PlayScene()
{
}

void PlayScene::Initialize()
{
    MessageBoxA(
        nullptr,
        "PlayScene Initialize",
        "Debug",
        MB_OK
    );

    model_ = Model::Load("Assets/tree.obj");

    transform_.position =
        Vector3(0.0f, 0.0f, 5.0f);

    Model::SetTransform(
        model_,
        transform_);
}

void PlayScene::Update()
{
    OutputDebugStringA("PlayScene\n");
}

void PlayScene::Draw()
{
    if (model_ != -1)
    {
        Model::Draw(model_);
    }
}