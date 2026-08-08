#pragma once

#include "GameObject.h"

class Scene : public GameObject
{
public:
    Scene(const std::string& name);
    virtual ~Scene();

    virtual void Initialize() {}

    virtual void Update() override;
    virtual void Draw() override;

    Scene* GetNextScene() const;

private:
    Scene* nextScene_ = nullptr;

protected:
    void SetNextScene(Scene* scene);
};