#include "AnimBase.hlsli"

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

struct Vtx3D_Out
{
    float4 Pos : SV_Position;
};

struct DeferredOut
{
    float4 OutColor : SV_Target6;
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

Vtx3D_Out VS_Emission(Vtx3D_In _In)
{
    SkinningPos(_In.Pos, _In.Weight, _In.Index, FrameAniTex);

    Vtx3D_Out Out = (Vtx3D_Out) 0;
    Out.Pos = mul(_In.Pos, WVP);
    return Out;
}

DeferredOut PS_Emission(Vtx3D_Out _In)
{
    DeferredOut Out = (DeferredOut) 0.0f;
    Out.OutColor.xw = 1.0f;
    return Out;
}
