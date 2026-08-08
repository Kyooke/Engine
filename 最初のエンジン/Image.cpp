#include "Image.h"
#include "Graphics.h"

#include <WICTextureLoader.h>
#include <vector>
#include <string>
#include <cstring>

struct ImageData
{
    ID3D11ShaderResourceView* texture = nullptr;
};

static std::vector<ImageData> images;

Graphics* Image::graphics_ = nullptr;

void Image::Initialize(Graphics* graphics)
{
    graphics_ = graphics;
}

int Image::Load(const char* fileName)
{
    if (graphics_ == nullptr)
    {
        return -1;
    }

    ImageData image;

    // Assets/ を自動で付ける
    std::wstring path = L"Assets/";

    path += std::wstring(
        fileName,
        fileName + strlen(fileName));

    HRESULT hr = DirectX::CreateWICTextureFromFile(
        graphics_->GetDevice(),
        path.c_str(),
        nullptr,
        &image.texture);

    if (FAILED(hr))
    {
        return -1;
    }

    images.push_back(image);

    return (int)images.size() - 1;
}

void Image::Release(int handle)
{
    if (handle < 0 ||
        handle >= (int)images.size())
    {
        return;
    }

    if (images[handle].texture)
    {
        images[handle].texture->Release();
        images[handle].texture = nullptr;
    }
}

void Image::Set(int handle)
{
    if (handle < 0 ||
        handle >= (int)images.size())
    {
        return;
    }

    graphics_->GetContext()->PSSetShaderResources(
        0,
        1,
        &images[handle].texture);
}