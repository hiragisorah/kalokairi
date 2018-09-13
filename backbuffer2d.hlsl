#include "constant_buffer.hlsli"

Texture2D tex : register(t0);

SamplerState own_sampler : register(s0);

struct VsOut
{
    float4 sv_position_ : SV_Position;
    float2 uv_ : TEXCOORD0;
};

struct PsOut
{
    float4 color_ : SV_Target0;
};

VsOut VS(uint index : SV_VertexID)
{
    VsOut output = (VsOut) 0;
 
    float2 uv = float2(index & 1, index >> 1);
    float4 position = float4(uv.x * 2 - 1, -(uv.y * 2 - 1), 0, 1);

    output.sv_position_ = mul(position, g_world);
    output.uv_ = uv;

    return output;
}

PsOut PS(VsOut input)
{
    PsOut output = (PsOut) 0;

    float4 color_ = tex.Sample(own_sampler, input.uv_);

    output.color_ = color_ * g_color;

    return output;
}