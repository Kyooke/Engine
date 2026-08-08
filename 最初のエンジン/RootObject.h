#pragma once

#include "GameObject.h"

class SceneManager;

class RootObject : public GameObject
{
public:

    RootObject();

    virtual ~RootObject();

    void Update() override;

    void Draw() override;

private:

    SceneManager* sceneManager_;
};