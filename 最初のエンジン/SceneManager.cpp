#include "SceneManager.h"
#include "Scene.h"
#include "TitleScene.h"
#include <Windows.h>

SceneManager::SceneManager()
    : GameObject("SceneManager")
{
    ChangeScene(new TitleScene());
}

SceneManager::~SceneManager()
{
    delete currentScene_;
    currentScene_ = nullptr;
}

void SceneManager::Update()
{
    if (currentScene_ != nullptr)
    {
        currentScene_->UpdateSub();
    }
    if (currentScene_->GetNextScene() != nullptr)
    {
        ChangeScene(currentScene_->GetNextScene());
    }
}

void SceneManager::Draw()
{
    if (currentScene_ != nullptr)
    {
        currentScene_->DrawSub();
    }
}

void SceneManager::ChangeScene(Scene* scene)
{
    MessageBoxA(
        nullptr,
        "ChangeScene",
        "Debug",
        MB_OK
    );

    if (currentScene_ != nullptr)
    {
        delete currentScene_;
    }

    currentScene_ = scene;

    if (currentScene_ != nullptr)
    {
        currentScene_->Initialize();
    }
}