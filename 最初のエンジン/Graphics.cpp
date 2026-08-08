#include "Graphics.h"
#include "Transform.h"
#include "Model.h"
#include "Vertex.h"
#include "Image.h"

#include <Windows.h>

struct ConstantBuffer
{
    DirectX::XMMATRIX world;
    DirectX::XMMATRIX view;
    DirectX::XMMATRIX projection;
};

bool Graphics::Initialize(
    HWND hwnd,
    int width,
    int height)
{
    DXGI_SWAP_CHAIN_DESC swapChainDesc = {};

    swapChainDesc.BufferCount = 1;
    swapChainDesc.BufferDesc.Width = width;
    swapChainDesc.BufferDesc.Height = height;
    swapChainDesc.BufferDesc.Format =
        DXGI_FORMAT_R8G8B8A8_UNORM;

    swapChainDesc.BufferUsage =
        DXGI_USAGE_RENDER_TARGET_OUTPUT;

    swapChainDesc.OutputWindow = hwnd;

    swapChainDesc.SampleDesc.Count = 1;

    swapChainDesc.Windowed = TRUE;

    HRESULT hr =
        D3D11CreateDeviceAndSwapChain(
            nullptr,
            D3D_DRIVER_TYPE_HARDWARE,
            nullptr,
            0,
            nullptr,
            0,
            D3D11_SDK_VERSION,
            &swapChainDesc,
            &swapChain_,
            &device_,
            nullptr,
            &context_);

    if (FAILED(hr))
    {
        return false;
    }

    //------------------------------------
    // BackBuffer取得
    //------------------------------------

    ID3D11Texture2D* backBuffer = nullptr;

    hr = swapChain_->GetBuffer(
        0,
        __uuidof(ID3D11Texture2D),
        (void**)&backBuffer);

    if (FAILED(hr))
    {
        return false;
    }

    hr = device_->CreateRenderTargetView(
        backBuffer,
        nullptr,
        &renderTargetView_);

    backBuffer->Release();

    if (FAILED(hr))
    {
        return false;
    }

    //------------------------------------
    // Viewport
    //------------------------------------

    viewport_.TopLeftX = 0.0f;
    viewport_.TopLeftY = 0.0f;
    viewport_.Width = (FLOAT)width;
    viewport_.Height = (FLOAT)height;
    viewport_.MinDepth = 0.0f;
    viewport_.MaxDepth = 1.0f;

    //------------------------------------
    // DepthBuffer
    //------------------------------------

    D3D11_TEXTURE2D_DESC depthDesc = {};

    depthDesc.Width = width;
    depthDesc.Height = height;
    depthDesc.MipLevels = 1;
    depthDesc.ArraySize = 1;
    depthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthDesc.SampleDesc.Count = 1;
    depthDesc.BindFlags =
        D3D11_BIND_DEPTH_STENCIL;

    hr = device_->CreateTexture2D(
        &depthDesc,
        nullptr,
        &depthStencilBuffer_);

    if (FAILED(hr))
    {
        MessageBoxW(
            nullptr,
            L"DepthBuffError",
            L"Error",
            MB_OK);

        return false;
    }

    hr = device_->CreateDepthStencilView(
        depthStencilBuffer_,
        nullptr,
        &depthStencilView_);

    if (FAILED(hr))
    {
        MessageBoxW(
            nullptr,
            L"DepthStencilViewError",
            L"Error",
            MB_OK);

        return false;
    }
    //------------------------------------
// VertexShader
//------------------------------------

    ID3DBlob* vertexBlob = nullptr;

    hr = D3DReadFileToBlob(
        L"Assets/Shaders/VertexShader.cso",
        &vertexBlob);

    if (FAILED(hr))
    {
        wchar_t currentPath[MAX_PATH] = {};

        GetCurrentDirectoryW(
            MAX_PATH,
            currentPath);

        MessageBoxW(
            nullptr,
            currentPath,
            L"現在の作業フォルダ",
            MB_OK);

        return false;
    }

    hr = device_->CreateVertexShader(
        vertexBlob->GetBufferPointer(),
        vertexBlob->GetBufferSize(),
        nullptr,
        &vertexShader_);

    if (FAILED(hr))
    {
        MessageBoxW(
            nullptr,
            L"VertexShaderError",
            L"Error",
            MB_OK);

        vertexBlob->Release();
        return false;
    }
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        {
            "POSITION",
            0,
            DXGI_FORMAT_R32G32B32_FLOAT,
            0,
            0,
            D3D11_INPUT_PER_VERTEX_DATA,
            0
        },
        {
            "TEXCOORD",
            0,
            DXGI_FORMAT_R32G32_FLOAT,
            0,
            12,
            D3D11_INPUT_PER_VERTEX_DATA,
            0
        },
        {
            "NORMAL",
            0,
            DXGI_FORMAT_R32G32B32_FLOAT,
            0,
            20,
            D3D11_INPUT_PER_VERTEX_DATA,
            0
        }
    };

    hr = device_->CreateInputLayout(
        layout,
        3,
        vertexBlob->GetBufferPointer(),
        vertexBlob->GetBufferSize(),
        &inputLayout_);

    vertexBlob->Release();

    if (FAILED(hr))
    {
        MessageBoxW(
            nullptr,
            L"InputLayoutError",
            L"Error",
            MB_OK);

        return false;
    }
    //------------------------------------
// PixelShader
//------------------------------------

    ID3DBlob* pixelBlob = nullptr;

    hr = D3DReadFileToBlob(
        L"Assets/Shaders/PixelShader.cso",
        &pixelBlob);

    if (FAILED(hr))
    {
        MessageBoxW(
            nullptr,
            L"PixelShader.cso を読み込めませんでした",
            L"Error",
            MB_OK);

        return false;
    }

    hr = device_->CreatePixelShader(
        pixelBlob->GetBufferPointer(),
        pixelBlob->GetBufferSize(),
        nullptr,
        &pixelShader_);

    pixelBlob->Release();

    if (FAILED(hr))
    {
        MessageBoxW(
            nullptr,
            L"PixelShaderError",
            L"Error",
            MB_OK);

        return false;
    }
 //------------------------------------
// ConstantBuffer
// //------------------------------------

    D3D11_BUFFER_DESC cbDesc = {};

    cbDesc.ByteWidth = sizeof(ConstantBuffer);
    cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cbDesc.Usage = D3D11_USAGE_DEFAULT;

    hr = device_->CreateBuffer(
        &cbDesc,
        nullptr,
        &constantBuffer_);

    if (FAILED(hr))
    {
        MessageBoxW(
            nullptr,
            L"ConstantBufferError",
            L"Error",
            MB_OK);

        return false;
    }

    D3D11_SAMPLER_DESC samplerDesc = {};

    samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

    hr = device_->CreateSamplerState(
        &samplerDesc,
        &samplerState_);

    if (FAILED(hr))
    {
        MessageBoxW(
            nullptr,
            L"SamplerStateError",
            L"Error",
            MB_OK);

        return false;
    }

    Model::Initialize(this);
    Image::Initialize(this);

    return true;
}

void Graphics::BeginFrame()
{
    float clearColor[] =
    {
        0.0f,
        0.0f,
        0.0f,
        1.0f
    };

    //-----------------------------
    // 描画先設定
    //-----------------------------

    context_->OMSetRenderTargets(
        1,
        &renderTargetView_,
        depthStencilView_);

    //-----------------------------
    // Viewport設定
    //-----------------------------

    context_->RSSetViewports(
        1,
        &viewport_);

    //-----------------------------
    // 画面クリア
    //-----------------------------

    context_->ClearRenderTargetView(
        renderTargetView_,
        clearColor);

    context_->ClearDepthStencilView(
        depthStencilView_,
        D3D11_CLEAR_DEPTH,
        1.0f,
        0);

    //-----------------------------
    // Shader設定
    //-----------------------------

    context_->VSSetShader(
        vertexShader_,
        nullptr,
        0);

    context_->PSSetShader(
        pixelShader_,
        nullptr,
        0);

    context_->PSSetSamplers(
        0,
        1,
        &samplerState_);
    //-----------------------------
    // InputLayout設定
    //-----------------------------

    context_->IASetInputLayout(
        inputLayout_);
    //-----------------------------
    // 三角形として描画
    //-----------------------------

    context_->IASetPrimitiveTopology(
        D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void Graphics::EndFrame()
{
    swapChain_->Present(
        1,
        0);
}

void Graphics::DrawModel(const Transform& transform)
{
    ConstantBuffer cb;

    cb.world =
        DirectX::XMMatrixTranspose(
            transform.GetWorldMatrix());

    cb.view =
        DirectX::XMMatrixTranspose(
            camera_.GetViewMatrix());

    cb.projection =
        DirectX::XMMatrixTranspose(
            DirectX::XMMatrixPerspectiveFovLH(
                DirectX::XMConvertToRadians(45.0f),
                viewport_.Width / viewport_.Height,
                0.1f,
                1000.0f));

    context_->UpdateSubresource(
        constantBuffer_,
        0,
        nullptr,
        &cb,
        0,
        0);

    context_->VSSetConstantBuffers(
        0,
        1,
        &constantBuffer_);
}