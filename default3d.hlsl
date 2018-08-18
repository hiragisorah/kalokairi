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
    output.normal_.xyz = input.normal_;
    //output.normal_.xyz = mul(input.normal_, (float3x3) g_world);
    output.uv_ = input.uv_;

    output.light_dir_ = normalize(float3(50.f, -30.f, 0));
    output.eye_dir_ = normalize(g_eye - output.position_.xyz);

    return output;
}

PsOut PS(VsOut input)
{
    PsOut output = (PsOut) 0;

    input.normal_.xyz = normalize(mul(input.normal_.xyz, (float3x3) g_world));

    float3 eye_dir = normalize(g_eye);
    float3 light_dir = normalize(float3(0.f, -10.f, 5.f));

    float dotL = dot(input.normal_.xyz, light_dir);
    float dotE = dot(input.normal_.xyz, eye_dir);
   
   // アークコサインで内積の結果からラジアン角を計算する
    float angleL = acos(dotL);
    float angleE = acos(dotE);
   
    float alpha = max(angleL, angleE);
    float beta = min(angleL, angleE);
   
   // 法線と垂直な平面へ射影したライトベクトル
    float3 al = light_dir - input.normal_.xyz * dotL;
   // 法線と垂直な平面へ射影した視線ベクトル
    float3 ae = g_eye.xyz - input.normal_.xyz * dotE;
    float gamma = max(0.0f, dot(al, ae));
   
    float g_fRoughness = 0.5f;

    float roughnessSquared = g_fRoughness * g_fRoughness;
   
   // 元の式では0.57ではなく0.33だが、相互反射成分がないために生じる不一致は、0.57を使用することによって部分的に補うことができるとか。
   // 要するに簡易版ではこうするといいということだろ、きっと。
    float A = 1.0f - 0.5f * (roughnessSquared / (roughnessSquared + 0.57f));
    float B = 0.45f * (roughnessSquared / (roughnessSquared + 0.09f));

   // max(0.0f, dotL) -> ランバート反射
    float l = max(0.0f, dotL) * (A + B * gamma * sin(alpha) * tan(beta));

    //output.color_ = tex.Sample(own_sampler, input.uv_);
    //output.color_ = float4(1 - diffuse, 1.f);
    //output.color_ = input.normal_;

    output.color_ = (float4(1, 1, 1, 1) * l).bgra;

    return output;
}