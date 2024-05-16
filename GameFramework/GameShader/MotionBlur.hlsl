#include "AnimBase.hlsli"
#include "RenderBase.hlsli"

struct Vtx3D_In
{
    float4 Pos : POSITION;
    float4 Uv : TEXCOORD;
    float4 Color : COLOR;
    float4 Normal : NORMAL; 
    float4 BiNormal : BINORMAL; 
    float4 Tangent : TANGENT; 
    float4 Weight : BLENDWEIGHT; 
    int4 Index : BLENDINDICES; 
};

struct  Vtx3D_Out
{
    float4 Pos : SV_Position;
    float4 Uv : TEXCOORD;
    float4 Color : COLOR;
};

struct OutColor
{
    float4 OutColor : SV_Target7;
};

Texture2D FrameAniTex : register(t0);

cbuffer TransData : register(b0)
{
    matrix POS;
    matrix SCALE;
    matrix ROT;
    matrix REVOL;
    matrix PARENT;
    matrix LWORLD;
    matrix WWORLD;
    matrix VIEW;
    matrix PROJ;
    matrix WV;
    matrix VP;
    matrix WVP;
}

cbuffer RenderOption : register(b7)
{
    RenderOptionBase RenderOptionData;
}

Vtx3D_Out VS_MotionBlur(Vtx3D_In _In)
{
    _In.Pos.w = 1.0F;
    _In.Normal.w = 0.0f;
    SkinningPos(_In.Pos, _In.Weight, _In.Index, FrameAniTex);
    
    Vtx3D_Out Out = (Vtx3D_Out) 0;
    Out.Pos = mul(_In.Pos, WVP);
    Out.Uv = _In.Uv;
    Out.Color = _In.Color;
    Out.Color.w = 1.0f;
    return Out;
}

Texture2D Tex : register(t0);
SamplerState Smp : register(s0);

OutColor PS_MotionBlur(Vtx3D_Out _In)
{
    OutColor Out = (OutColor) 0.0f;

    if (0 != RenderOptionData.IsDifTexture)
    {
        Out.OutColor = Tex.Sample(Smp, _In.Uv.xy);
    }
    else
    {
        Out.OutColor = RenderOptionData.BasicColor;
    }
   
    Out.OutColor.w = 1.0f;
    return Out;
}
