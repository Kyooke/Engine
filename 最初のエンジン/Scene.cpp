#include "Scene.h"

Scene::Scene(const std::string& name)
    : GameObject(name)
{
}

Scene::~Scene()
{
}

void Scene::Update()
{
}

void Scene::Draw()
{
}

Scene* Scene::GetNextScene() const
{
    return nextScene_;
}

void Scene::SetNextScene(Scene* scene)
{
    nextScene_ = scene;
}
