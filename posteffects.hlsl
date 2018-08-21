#include "constant_buffer.hlsli"

Texture2D color_tex : register(t0);
Texture2D position_tex : register(t1);
Texture2D normal_depth_tex : register(t2);
Texture2D screen_tex : register(t3);

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

    output.sv_position_ = position;
    output.uv_ = uv;

    return output;
}

float peek(float x, float y)
{
    return normal_depth_tex.Sample(own_sampler, float2(x, y)).w;
}

float3 peek2(float x, float y)
{
    return normal_depth_tex.Sample(own_sampler, float2(x, y)).xyz;
}

float4 peek3(float x, float y)
{
    return screen_tex.Sample(own_sampler, float2(x, y));
}

PsOut PS(VsOut input)
{
    PsOut output = (PsOut) 0;
    
    // - GBuffer
    float4 color_ = color_tex.Sample(own_sampler, input.uv_);
    float4 position_ = position_tex.Sample(own_sampler, input.uv_);
    float3 normal_ = normal_depth_tex.Sample(own_sampler, input.uv_).xyz;
    float3 depth_ = normal_depth_tex.Sample(own_sampler, input.uv_).w;
    float4 screen_ = screen_tex.Sample(own_sampler, input.uv_);
    // GBuffer -

    //float x = 1 / g_view_port.x;
    //float y = 1 / g_view_port.y;
    //float u = input.uv_.x;
    //float v = input.uv_.y;
    //float4 screen_avg = 0;
    
    //for (int w = -1; w < 2; w++)
    //{
    //    for (int h = -1; h < 2; h++)
    //    {
    //        screen_avg += peek3(u + w * x, v + h * y);
    //    }
    //}

    //screen_avg /= 9.f;

    //output.color_ = screen_avg;
    output.color_ = screen_;

    return output;
}