cbuffer ConstantBuffer : register(b0)
{
    matrix world;
    matrix view;
    matrix projection;

    float4 lightDirection;
};

struct VS_INPUT
{
    float3 pos : POSITION;
    float2 uv : TEXCOORD0;
    float3 normal : NORMAL;
};

struct VS_OUTPUT
{
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD0;
};

VS_OUTPUT main(VS_INPUT input)
{
    VS_OUTPUT output;

    float4 position = float4(input.pos, 1.0f);

    position = mul(position, world);
    position = mul(position, view);
    position = mul(position, projection);

    output.pos = position;
    output.uv = input.uv;

    return output;
}