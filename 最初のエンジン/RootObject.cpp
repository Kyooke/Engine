#include "RootObject.h"
#include "SceneManager.h"

RootObject::RootObject()
    : GameObject("RootObject")
{
    sceneManager_ = new SceneManager();

    AddChild(sceneManager_);
}

RootObject::~RootObject()
{

}

void RootObject::Update()
{

}

void RootObject::Draw()
{

}