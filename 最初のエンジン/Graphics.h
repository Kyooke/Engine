#pragma once

#include <Windows.h>
#include <dxgi.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#include "Camera.h"

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"d3dcompiler.lib")

class Mesh;

class Graphics
{
public:

    bool Initialize(
        HWND hwnd,
        int width,
        int height);

    void BeginFrame();

    void EndFrame();

    void DrawModel(const Transform& transform);



    ID3D11Device* GetDevice()
    {
        return device_;
    }

    ID3D11DeviceContext* GetContext()
    {
        return context_;
    }

    Camera& GetCamera()
    {
        return camera_;
    }

private:

    ID3D11Device* device_ = nullptr;

    ID3D11DeviceContext* context_ = nullptr;

    IDXGISwapChain* swapChain_ = nullptr;

    ID3D11RenderTargetView* renderTargetView_ = nullptr;

    ID3D11VertexShader* vertexShader_ = nullptr;

    ID3D11PixelShader* pixelShader_ = nullptr;

    ID3D11InputLayout* inputLayout_ = nullptr;

    ID3D11Buffer* constantBuffer_ = nullptr;

    ID3D11Texture2D* depthStencilBuffer_ = nullptr;

    ID3D11DepthStencilView* depthStencilView_ = nullptr;

    D3D11_VIEWPORT viewport_;

    ID3D11SamplerState* samplerState_ = nullptr;

    Camera camera_;
};