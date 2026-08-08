#pragma once

#include "GameObject.h"

class Scene;

class SceneManager : public GameObject
{
public:
    SceneManager();

    virtual ~SceneManager();

    void Update() override;

    void Draw() override;

    void ChangeScene(Scene* scene);
private:

    Scene* currentScene_ = nullptr;
};