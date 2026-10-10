cbuffer ConstantBuffer : register(b0)
{
    matrix world;
    matrix view;
    matrix projection;

    float4 lightDirection;
};

struct VS_OUTPUT
{
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD0;
    float3 normal : NORMAL;
};

float4 main(VS_OUTPUT input) : SV_TARGET
{
    // 法線を正規化
    float3 normal =
        normalize(input.normal);

    // ライト方向を正規化
    float3 light =
        normalize(-lightDirection.xyz);

    // 法線とライトの角度
    float brightness =
        max(
            dot(normal, light),
            0.0f);

    // 環境光
    brightness =
        brightness * 0.8f + 0.2f;

    return float4(
        brightness,
        brightness,
        brightness,
        1.0f);
}