#pragma once

#include "Transform.h"

#include <string>
#include <list>

class Model;

class GameObject
{
public:

    GameObject(
        const std::string& name);

    virtual ~GameObject();

    // 毎フレーム更新
    virtual void Update();

    // 描画
    virtual void Draw();

    // 自分＋子を更新
    void UpdateSub();

    // 自分＋子を描画
    void DrawSub();

    // 子を追加
    void AddChild(GameObject* child);

    // Transform取得
    Transform& GetTransform();

    // 名前取得
    const std::string& GetName() const;

    void SetModelHandle(int handle);

    int GetModelHandle() const;

protected:

    Transform transform_;

    int modelHandle_ = -1;

private:

    std::string name_;

    GameObject* parent_ = nullptr;

    std::list<GameObject*> children_;
};