#include "constant_buffer.hlsli"

struct VsIn
{
    float3 position_ : POSITION;
};

struct VsOut
{
    float4 sv_position_ : SV_Position;
    float4 depth_ : POSITION;
};

struct PsOut
{
    float depth_ : SV_Target0;
};

VsOut VS(VsIn input)
{
    VsOut output = (VsOut) 0;

    matrix wlp = mul(g_world, mul(g_light_view, g_light_proj));

    output.sv_position_ = mul(float4(input.position_, 1.f), wlp);
    output.depth_ = output.sv_position_;

    return output;
}

PsOut PS(VsOut input)
{
    PsOut output = (PsOut) 0;

    output.depth_ = input.depth_.z / input.depth_.w;

    return output;
}