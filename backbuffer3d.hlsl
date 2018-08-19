#include "constant_buffer.hlsli"

Texture2D color_tex : register(t0);
Texture2D position_tex : register(t1);
Texture2D normal_tex : register(t2);
Texture2D depth_tex : register(t3);

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
    return depth_tex.Sample(own_sampler, float2(x, y)).r;
}

float3 peek2(float x, float y)
{
    return normal_tex.Sample(own_sampler, float2(x, y)).xyz;
}

static float dx = 0.0015;
static float dy = 0.0015;

PsOut PS(VsOut input)
{
    PsOut output = (PsOut) 0;
    
    // - GBuffer
    float4 color_ = color_tex.Sample(own_sampler, input.uv_);
    float4 position_ = position_tex.Sample(own_sampler, input.uv_);
    float4 normal_ = normal_tex.Sample(own_sampler, input.uv_);
    float4 depth_ = depth_tex.Sample(own_sampler, input.uv_);
    // GBuffer -

    // 陰影 
    float3 light_dir = normalize(g_dir_light - position_.xyz);

    float dotL = dot(normal_.xyz, light_dir);
    //

    // - テカり
    float3 eye_dir = normalize(g_eye - position_.xyz);

    float dotE = dot(normal_.xyz, eye_dir);
    
    // テカり -

    // - トゥーン（3値化?）
    float l = max(0.0f, dotL);
    l = min(lerp(step(0.02f, l) * 0.3f, 0.4f, step(0.5, l)) + 0.6f, 1.0);

    // トゥーン（3値化?） - 
    
    // -　アウトライン
    float x = input.uv_.x;
    float y = input.uv_.y;
    
    float b = peek(x, y);
    float2 d;
    
    d.x = step(0.01f, abs(b - peek(x + dx, y))
          + abs(b - peek(x, y + dy)));

    float3 b2 = peek2(x, y);

    d.y = 1.f - step(float3(1.9f, 1.9f, 1.9f), abs(dot(b2, peek2(x + dx, y)))
          + abs(dot(b2, peek2(x, y + dy))));

    float out_line = 1.0 - min(d.x + d.y, 1.f);
    // outline -

    output.color_ = color_ * l * out_line;

    return output;
}