#pragma once

#include "Scene.h"

class TitleScene : public Scene
{
public:
    TitleScene();
    virtual ~TitleScene();

    void Update() override;
    void Draw() override;
};