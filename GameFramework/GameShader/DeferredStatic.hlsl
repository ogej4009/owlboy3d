#include "LightBase.hlsli"
#include "AnimBase.hlsli"
#include "RenderBase.hlsli"

struct BaseVtx_In
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
};

cbuffer TransData : register(b0)
{
    TransDataBase MatrixData;
}

cbuffer RenderOption : register(b7)
{
    RenderOptionBase RenderOptionData;
}

Texture2D FrameAniTex : register(t0);

Vtx3D_Out VS_DeferredStatic(BaseVtx_In _In)
{
    _In.Pos.w = 1.0F;
    _In.Normal.y = mul(-1.0f, _In.Normal.y);
    _In.Normal.w = 0.0f;
    
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
    Out.ViewNormal = normalize(mul(_In.Normal, MatrixData.WV));
    _In.Normal.w = 0.0f;
    return Out;
}

struct DeferredOut
{
    float4 DifColor : SV_Target0;
    float4 PosColor : SV_Target1;
    float4 NorColor : SV_Target2;
    float4 DepColor : SV_Target3;
};

Texture2D Tex : register(t0);
SamplerState Smp : register(s0);

DeferredOut PS_DeferredStatic(Vtx3D_Out _In)
{
    DeferredOut Out = (DeferredOut) 0;

    if (0 != RenderOptionData.IsDifTexture)
    {
        Out.DifColor = Tex.Sample(Smp, _In.Uv.xy);
    }
    else
    {
        Out.DifColor = RenderOptionData.BasicColor;
    }

    Out.NorColor = _In.ViewNormal;
    Out.PosColor = _In.ViewPos;
    Out.DepColor.x = _In.ViewPos.z;
    Out.DifColor.w = 1.0f;
    Out.DepColor.w = Out.PosColor.w = Out.NorColor.w = 1.0f;
    return Out;
}
