#include "constant_buffer.hlsli"

Texture2D tex : register(t0);

SamplerState own_sampler : register(s0);

struct VsIn
{
    float3 position_ : POSITION;
    float3 normal_ : NORMAL;
    float2 uv_ : TEXCOORD;
};

struct VsOut
{
    float4 sv_position_ : SV_Position;
    float4 position_ : TEXCOORD0;
    float3 normal_ : TEXCOORD1;
    float2 uv_ : TEXCOORD2;
};

struct PsOut
{
    float4 color_ : SV_Target0;
    float4 position_ : SV_Target1;
    float4 normal_depth_ : SV_Target2;
};

VsOut VS(VsIn input)
{

    VsOut output = (VsOut) 0;

    matrix wvp = mul(g_world, mul(g_view, g_proj));

    output.sv_position_ = mul(float4(input.position_, 1.f), wvp);
    output.position_ = mul(float4(input.position_, 1.f), g_world);
    output.normal_.xyz = input.normal_;
    //output.normal_.xyz = mul(input.normal_, (float3x3) g_world);
    output.uv_ = input.uv_;

    return output;
}

float isDithered(float2 pos, float alpha)
{


    // Define a dither threshold matrix which can
    // be used to define how a 4x4 set of pixels
    // will be dithered
    float DITHER_THRESHOLDS[16] =
    {
        1.0 / 17.0, 9.0 / 17.0, 3.0 / 17.0, 11.0 / 17.0,
        13.0 / 17.0, 5.0 / 17.0, 15.0 / 17.0, 7.0 / 17.0,
        4.0 / 17.0, 12.0 / 17.0, 2.0 / 17.0, 10.0 / 17.0,
        16.0 / 17.0, 8.0 / 17.0, 14.0 / 17.0, 6.0 / 17.0
    };

    int index = (int(pos.x) % 4) * 4 + int(pos.y) % 4;
    return alpha - DITHER_THRESHOLDS[index];
}

void ditherClip(float2 pos, float alpha)
{
    clip(isDithered(pos, alpha));
}

PsOut PS(VsOut input)
{
    PsOut output = (PsOut) 0;

    ditherClip(input.sv_position_.xy, g_color.a);

    output.color_ = g_color;
    output.position_ = input.position_;
    //output.normal_ = input.normal_;
    output.normal_depth_.xyz = normalize(mul(input.normal_.xyz, (float3x3) g_world));
    output.normal_depth_.w = input.sv_position_.z / input.sv_position_.w;

    output.color_.a = 1;
    output.position_.a = 1;

    return output;
}