cbuffer main : register(b0)
{
    row_major matrix g_view : packoffset(c0);
    row_major matrix g_proj : packoffset(c4);
    row_major matrix g_light_view : packoffset(c8);
    row_major matrix g_light_proj : packoffset(c12);
    row_major matrix g_tex_uv : packoffset(c16);
    float3 g_eye : packoffset(c20);
    float3 g_dir_light : packoffset(c21);
    int g_timer : packoffset(c22);
    float2 g_view_port : packoffset(c23);
};

cbuffer world : register(b1)
{
    row_major matrix g_world : packoffset(c0);
    float4 g_color : packoffset(c4);
};