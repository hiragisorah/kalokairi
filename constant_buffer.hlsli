cbuffer main : register(b0)
{
    row_major matrix g_view : packoffset(c0);
    row_major matrix g_proj : packoffset(c4);
    float3 g_eye : packoffset(c8);
    float3 g_dir_light : packoffset(c9);
};

cbuffer world : register(b1)
{
    row_major matrix g_world : packoffset(c0);
};