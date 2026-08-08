#include "GameObject.h"
#include "Transform.h"
#include "Model.h"


GameObject::GameObject(const std::string& name)
    :name_(name)
{

}


GameObject::~GameObject()
{
    for (auto child : children_)
    {
        delete child;
    }

    children_.clear();
}


void GameObject::Update()
{

}


void GameObject::Draw()
{
    if (modelHandle_ >= 0)
    {
        Model::SetTransform(
            modelHandle_,
            transform_);

        Model::Draw(
            modelHandle_);
    }
}


const std::string& GameObject::GetName() const
{
    return name_;
}

void GameObject::SetModelHandle(int handle)
{
}

int GameObject::GetModelHandle() const
{
    return 0;
}

void GameObject::UpdateSub()
{
    //自分を更新
    Update();


    //子を更新
    for (auto child : children_)
    {
        child->UpdateSub();
    }
}

void GameObject::DrawSub()
{
    //自分を描画
    Draw();


    //子を描画
    for (auto child : children_)
    {
        child->DrawSub();
    }
}
Transform& GameObject::GetTransform()
{
    return transform_;
}

void GameObject::AddChild(GameObject* child)
{
    if (child == nullptr)
    {
        return;
    }


    child->parent_ = this;


    children_.push_back(child);
}