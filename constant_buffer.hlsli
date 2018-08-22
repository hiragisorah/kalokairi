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

// Returns whether the pixel should be discarded based
// on the dither texture
// pos is the fragment position in screen space from [0,1]
//float isDithered(float2 pos, float alpha, Texture2D tex, float scale)
//{
//    pos *= g_view_port.xy;

//    // offset so we're centered
//    pos.x -= g_view_port.x / 2;
//    pos.y -= g_view_port.y / 2;
    
//    // scale the texture
//    pos.x /= scale;
//    pos.y /= scale;

//	// ensure that we clip if the alpha is zero by
//	// subtracting a small value when alpha == 0, because
//	// the clip function only clips when < 0
//    return alpha - tex.Sample(tex, pos.xy).r - 0.0001 * (1 - ceil(alpha));
//}

// Helpers that call the above functions and clip if necessary

//void ditherClip(float2 pos, float alpha, sampler2D tex, float scale)
//{
//    clip(isDithered(pos, alpha, tex, scale));
//}