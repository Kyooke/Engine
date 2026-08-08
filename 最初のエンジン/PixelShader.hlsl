Texture2D tex : register(t0);
SamplerState sampler0 : register(s0);

struct VS_OUTPUT
{
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD0;
    float3 normal : NORMAL;
};

float4 main(VS_OUTPUT input) : SV_TARGET
{
    return tex.Sample(sampler0, input.uv);
}