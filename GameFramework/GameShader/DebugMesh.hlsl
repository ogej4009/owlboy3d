#include "BumpBase.hlsli"
#include "RenderBase.hlsli"
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
    float4 Uv : TEXCOORD;
    float4 Color : COLOR;
};

cbuffer TransData : register(b0)
{
    TransDataBase MatrixData;
}

cbuffer RenderOption : register(b8)
{
    RenderOptionBase RenderOptionData;
}

Vtx3D_Out VS_DebugMesh(Vtx3D_In _In)
{
    Vtx3D_Out Out = (Vtx3D_Out) 0;
    Out.Pos = mul(_In.Pos, MatrixData.WVP);
    Out.Color = _In.Color;
    return Out;
}

struct ForwardOut
{
    float4 ForwardColor : SV_Target0;
};

ForwardOut PS_DebugMesh(Vtx3D_Out _In)
{
    ForwardOut Out = (ForwardOut) 0.0f;
    Out.ForwardColor = _In.Color;
    return Out;
}
