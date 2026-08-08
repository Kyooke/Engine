#include "Mesh.h"
#include "Graphics.h"
#include "Vertex.h"
#include <vector>

bool Mesh::Initialize(Graphics* graphics, const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
{
    graphics_ = graphics;

    indexCount_ = (UINT)indices.size();

    D3D11_BUFFER_DESC ibDesc = {};
    ibDesc.ByteWidth = sizeof(unsigned int) * (UINT)indices.size();
    ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    ibDesc.Usage = D3D11_USAGE_DEFAULT;

    D3D11_SUBRESOURCE_DATA ibData = {};
    ibData.pSysMem = indices.data();

    D3D11_BUFFER_DESC vbDesc = {};
    vbDesc.ByteWidth = sizeof(Vertex) * (UINT)vertices.size();
    vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vbDesc.Usage = D3D11_USAGE_DEFAULT;

    D3D11_SUBRESOURCE_DATA vbData = {};
    vbData.pSysMem = vertices.data();
    graphics->GetDevice()->CreateBuffer(
        &vbDesc,
        &vbData,
        &vertexBuffer_);

    graphics->GetDevice()->CreateBuffer(
        &ibDesc,
        &ibData,
        &indexBuffer_);

    return true;
}

void Mesh::Draw(const Transform& transform)
{
    graphics_->DrawModel(transform);

    UINT stride = sizeof(Vertex);
    UINT offset = 0;

    graphics_->GetContext()->IASetVertexBuffers(
        0,
        1,
        &vertexBuffer_,
        &stride,
        &offset);

    graphics_->GetContext()->IASetIndexBuffer(
        indexBuffer_,
        DXGI_FORMAT_R32_UINT,
        0);

    graphics_->GetContext()->DrawIndexed(
        indexCount_,
        0,
        0);
}


