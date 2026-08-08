#include "TitleScene.h"
#include "Input.h"
#include "PlayScene.h"
#include <Windows.h>

TitleScene::TitleScene()
    : Scene("TitleScene")
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update()
{
    OutputDebugStringA("TitleScene\n");

    if (Input::IsKey(VK_RETURN))
    {
        SetNextScene(new PlayScene());
    }
}

void TitleScene::Draw()
{
}