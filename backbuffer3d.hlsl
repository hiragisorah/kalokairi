#include "constant_buffer.hlsli"

Texture2D color_tex : register(t0);
Texture2D position_tex : register(t1);
Texture2D normal_depth_tex : register(t2);
Texture2D shadow_map_tex : register(t3);

SamplerState own_sampler : register(s0);
SamplerComparisonState own_sampler_cmp : register(s1);

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

//static float dx = 0.0015;
//static float dy = 0.0015;

PsOut PS(VsOut input)
{
    PsOut output = (PsOut) 0;
    
    // - GBuffer
    float4 color_ = color_tex.Sample(own_sampler, input.uv_);
    float4 position_ = position_tex.Sample(own_sampler, input.uv_);
    float3 normal_ = normal_depth_tex.Sample(own_sampler, input.uv_).xyz;
    float depth_ = normal_depth_tex.Sample(own_sampler, input.uv_).w;
    float4 shadow_map_ = shadow_map_tex.Sample(own_sampler, input.uv_);
    // GBuffer -

    matrix lp = mul(g_light_view, g_light_proj);
    matrix lpt = mul(g_light_view, mul(g_light_proj, g_tex_uv));
    
    float4 light_uv = mul(position_, lpt);
    float4 light_pos = mul(position_, lp);
    //

    float3 shadowCoord = light_uv.xyz / light_uv.w;

    float maxDepthSlope = max(abs(ddx(shadowCoord.z)), abs(ddy(shadowCoord.z)));

    float shadowThreshold = 1.0f;

    float bias = 0.02f;
    float slopeScaledBias = 0.1f;

    float depthBiasClamp = 0.08f;

    float shadowBias = bias + slopeScaledBias * maxDepthSlope;

    shadowBias = min(shadowBias, depthBiasClamp);

    float3 shadowColor = 1;

    shadowThreshold = shadow_map_tex.SampleCmpLevelZero(own_sampler_cmp, shadowCoord.xy, shadowCoord.z - shadowBias);

    shadowColor = lerp(shadowColor, float3(0.3f, 0.3f, 0.3f), 1.f - shadowThreshold);

    color_.xyz *= shadowColor.xyz;

    // 陰影 
    float3 light_dir = normalize(g_dir_light - position_.xyz);

    float dotL = dot(normal_, light_dir);
    //

    // - テカり
    float3 eye_dir = normalize(g_eye - position_.xyz);

    float dotE = dot(normal_, eye_dir);

    // テカり -

    // - トゥーン（3値化?）
    float l = max(0.0f, dotL);

    l = min(lerp(step(0.02f, l) * 0.3f, 0.4f, step(0.5, l)) + 0.5f, 1.0);

    // トゥーン（3値化?） - 
    
    // -　アウトライン
    float x = input.uv_.x;
    float y = input.uv_.y;
    
    float b = peek(x, y);
    float2 d;

    float dx = 2 / g_view_port.x;
    float dy = 2 / g_view_port.y;
    
    d.x = step(0.01f, abs(b - peek(x + dx, y))
          + abs(b - peek(x, y + dy)));

    float3 b2 = peek2(x, y);

    d.y = 1.f - step(float3(1.9f, 1.9f, 1.9f), abs(dot(b2, peek2(x + dx, y)))
          + abs(dot(b2, peek2(x, y + dy))));

    float out_line = 1.0 - min(d.x + d.y, 1.f);
    // outline -

    output.color_ = color_ * l * out_line;

    //output.color_ = shadow_;
    //output.color_ = shadow_map_;

    return output;
}