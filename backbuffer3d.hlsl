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

float peek(float2 uv)
{
    return depth_tex.Sample(own_sampler, uv).r;
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

    float angleL = acos(dotL);
    float angleE = acos(dotE);

    float alpha = max(angleL, angleE);
    float beta = min(angleL, angleE);

    float3 al = light_dir - normal_.xyz * dotL;
    float3 ae = eye_dir - normal_.xyz * dotE;

    float gamma = max(0.0f, dot(al, ae));
    // テカり -


    // - トゥーン（3値化?）
    float l = max(0.0f, dotL);

    l = min(lerp(step(0.03f, l) * 0.3f, 0.4f, step(0.5, l)) + 0.5f + gamma, 1.0);

    // トゥーン（3値化?） - 
    
    // -　アウトライン
    float x = input.uv_.x;
    float y = input.uv_.y;
    
    float b = peek(x, y);
    float d = step(0.01f, abs(b - peek(x + dx, y))
          + abs(b - peek(x, y + dy)));

    float out_line = 1.0 - d;
    // outline -

    output.color_ = color_ * l * out_line;

    return output;
}