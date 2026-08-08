#pragma once

#include "Scene.h"

class ResultScene : public Scene
{
public:
    ResultScene();
    virtual ~ResultScene();

    void Update() override;
    void Draw() override;
};