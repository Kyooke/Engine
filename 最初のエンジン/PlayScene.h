#pragma once

#include "Scene.h"
#include "Model.h"
#include "Transform.h"

class PlayScene : public Scene
{
public:

    PlayScene();
    ~PlayScene();

    void Initialize() override;
    void Update() override;
    void Draw() override;


private:

    int model_ = -1;
    Transform transform_;
};