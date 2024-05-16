#include "LightBase.hlsli"
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
    float4 ViewPos : POSITION;
    float4 ViewNormal : NORMAL;
    float4 ViewBiNormal : BINORMAL;
    float4 ViewTangent : TANGENT;
};

cbuffer TransData : register(b0)
{
    TransDataBase MatrixData;
}

cbuffer RenderOption : register(b8)
{
    RenderOptionBase RenderOptionData;
}

Texture2D FrameAniTex : register(t0);

Vtx3D_Out VS_Forward(Vtx3D_In _In)
{
    if (0 != RenderOptionData.IsAni)
    {
        SkinningTex(_In.Pos, _In.Normal, _In.Weight, _In.Index, FrameAniTex);
    }

    Vtx3D_Out Out = (Vtx3D_Out) 0;
    Out.Pos = mul(_In.Pos, MatrixData.WVP);
    Out.Uv = _In.Uv;
    Out.Color = _In.Color;

    _In.Pos.w = 1.0f;
    Out.ViewPos = mul(_In.Pos, MatrixData.WV);

    _In.Normal.w = 0.0f;
    Out.ViewNormal = mul(_In.Normal, MatrixData.WV);

    _In.BiNormal.w = 0.0f;
    Out.ViewBiNormal = mul(_In.BiNormal, MatrixData.WV);

    _In.Tangent.w = 0.0f;
    Out.ViewTangent = mul(_In.Tangent, MatrixData.WV);

    return Out;
}

struct ForwardOut
{
    float4 ForwardColor : SV_Target0;
};

cbuffer LightData : register(b7)
{
    ObjectLightData ArrLightData;
}

Texture2D Tex : register(t0);
Texture2D NormalTexture : register(t1);
SamplerState Smp : register(s0);

ForwardOut PS_Forward(Vtx3D_Out _In)
{
    if (0 != RenderOptionData.IsNormalTexture)
    {
        _In.ViewNormal = CalBump(_In.ViewNormal, _In.ViewBiNormal, _In.ViewTangent, _In.Uv.xy, NormalTexture, Smp);
    }

    CalLightResult ResultLightColor = (CalLightResult) 0;

    for (int i = 0; i < ArrLightData.LightCount[0]; ++i)
    {
        if (0.0f == ArrLightData.ArrLightData[i].OnOff.x)
        {
            continue;
        }

        CalLightResult LightColor = CalDirLight(_In.ViewPos, _In.ViewNormal, ArrLightData.ArrLightData[i]);
        ResultLightColor.Amb += LightColor.Amb;
        ResultLightColor.Dif += LightColor.Dif;
        ResultLightColor.Spc += LightColor.Spc;
    }

    ForwardOut Out = (ForwardOut) 0;

    if (RenderOptionData.IsDifTexture != 0)
    {
        Out.ForwardColor = Tex.Sample(Smp, _In.Uv.xy);
        Out.ForwardColor.xyz *= (ResultLightColor.Dif.xyz + ResultLightColor.Spc.xyz + ResultLightColor.Amb.xyz);
    }
    else
    {
        Out.ForwardColor.xyz = RenderOptionData.BasicColor.xyz * (ResultLightColor.Dif.xyz + ResultLightColor.Spc.xyz + ResultLightColor.Amb.xyz);
        Out.ForwardColor.w = RenderOptionData.BasicColor.w;
    }

    return Out;
}
