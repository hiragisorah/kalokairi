Texture2D tex : register(t0);

SamplerState own_sampler : register(s0);

cbuffer unique : register(b0)
{
    row_major matrix g_world : packoffset(c0);
    row_major matrix g_view : packoffset(c4);
    row_major matrix g_proj : packoffset(c8);
    float3 g_eye : packoffset(c12);
};

//cbuffer camera : register(b1)
//{
//    row_major matrix g_v : packoffset(c0);
//    row_major matrix g_p : packoffset(c4);

//    float4 g_eye : packoffset(c8);
//    float4 g_at : packoffset(c9);

//    float2 g_view_port : packoffset(c10);

//    float4 g_color : packoffset(c11);
//};

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
    float4 normal_ : TEXCOORD1;
    float2 uv_ : TEXCOORD2;
    float3 light_dir_ : TEXCOORD4;
    float3 eye_dir_ : TEXCOORD5;
};

struct PsOut
{
    float4 color_ : SV_Target0;
};

VsOut VS(VsIn input)
{
    VsOut output = (VsOut) 0;

    matrix wvp = mul(g_world, mul(g_view, g_proj));

    output.sv_position_ = mul(float4(input.position_, 1.f), wvp);
    output.position_ = mul(float4(input.position_, 1.f), g_world);
    output.normal_.xyz = mul(input.normal_, (float3x3)g_world);
    output.uv_ = input.uv_;

    //ライト方向で入力されるので、頂点 -> ライト位置とするために逆向きに変換する。なおアプリケーションで必ず正規化すること
    output.light_dir_ = normalize(float3(50.f, -30.f, 0));
    output.eye_dir_ = normalize(g_eye - output.position_.xyz);

    return output;
}

PsOut PS(VsOut input)
{
    PsOut output = (PsOut) 0;
    float3 el = input.light_dir_ - input.eye_dir_;
    float3 diffuse = pow(saturate(dot(input.normal_.xyz, el)), float3(1, 1, 1));

    output.color_ = tex.Sample(own_sampler, input.uv_);
    output.color_ = float4(1 - diffuse, 1.f);
    output.color_ = input.normal_;

    return output;
}