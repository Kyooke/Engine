#pragma once
#include "Transform.h"
#include "Vertex.h"

#include <d3d11.h>
#include <vector>

class Graphics;

class Mesh
{
public:

    bool Initialize(Graphics* graphics,const std::vector<Vertex>& vertices,const std::vector<unsigned int>& indices);

    void Draw(const Transform& transform);

private:

    Graphics* graphics_ = nullptr;

    ID3D11Buffer* vertexBuffer_ = nullptr;
    ID3D11Buffer* indexBuffer_ = nullptr;

    UINT indexCount_ = 0;
};