Texture2D color_tex : register(t0);
Texture2D position_tex : register(t1);
Texture2D normal_tex : register(t2);

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

PsOut PS(VsOut input)
{
    PsOut output = (PsOut) 0;
    
    float4 color_ = color_tex.Sample(own_sampler, input.uv_);
    float4 position_ = position_tex.Sample(own_sampler, input.uv_);
    float4 normal_ = normal_tex.Sample(own_sampler, input.uv_);

    float3 g_eye = float3(0, 6, -6);

    float3 eye_dir = normalize(g_eye);
    float3 light_dir = normalize(float3(0.f, -10.f, 5.f));

    float dotL = dot(normal_.xyz, light_dir);
    float dotE = dot(normal_.xyz, eye_dir);
   
   // アークコサインで内積の結果からラジアン角を計算する
    float angleL = acos(dotL);
    float angleE = acos(dotE);
   
    float alpha = max(angleL, angleE);
    float beta = min(angleL, angleE);
   
   // 法線と垂直な平面へ射影したライトベクトル
    float3 al = light_dir - normal_.xyz * dotL;
   // 法線と垂直な平面へ射影した視線ベクトル
    float3 ae = g_eye.xyz - normal_.xyz * dotE;
    float gamma = max(0.0f, dot(al, ae));
   
    float g_fRoughness = 0.5f;

    float roughnessSquared = g_fRoughness * g_fRoughness;
   
   // 元の式では0.57ではなく0.33だが、相互反射成分がないために生じる不一致は、0.57を使用することによって部分的に補うことができるとか。
   // 要するに簡易版ではこうするといいということだろ、きっと。
    float A = 1.0f - 0.5f * (roughnessSquared / (roughnessSquared + 0.57f));
    float B = 0.45f * (roughnessSquared / (roughnessSquared + 0.09f));

   // max(0.0f, dotL) -> ランバート反射
    float l = max(0.0f, dotL) * (A + B * gamma * sin(alpha) * tan(beta));

    output.color_ = (float4(1, 1, 1, 1) * l).bgra;

    return output;
}