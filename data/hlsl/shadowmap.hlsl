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

float isDithered(float2 pos, float alpha)
{
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
    
    ditherClip(input.sv_position_.xy, g_color.a);

    output.depth_ = input.depth_.z / input.depth_.w;

    return output;
}