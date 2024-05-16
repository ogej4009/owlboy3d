#include "RenderBase.hlsli"

struct VtxIn
{
    float4 Pos : SHA_INIT_POSITION;
    float4 Uv : SHA_INIT_TEXCOORD;
    float4 Color : SHA_INIT_COLOR;
};

struct VtxOut
{
    float4 Pos : SV_Position;
    float4 Uv : TEXCOORD;
    float4 Color : COLOR;
};


cbuffer TransData : register(b0)
{
    TransDataBase TDB;
}

cbuffer RenderOptionData : register(b7)
{
    RenderOptionBase ROB;
}

cbuffer CutData : register(b1)
{
    SprCutDataBase SCDB;
};

VtxOut VS_GhostBurn(VtxIn _In)
{
    VtxOut Out = (VtxOut) 0;
    Out.Pos = mul(_In.Pos, TDB.WVP);
    Out.Uv = _In.Uv;
    Out.Color = _In.Color;
    return Out;
}


Texture2D Tex : register(t0);
Texture2D TexAdd : register(t1);
SamplerState Smp : register(s0);

float4 PS_GhostBurn(VtxOut _Out) : SV_Target0
{
    float4 Return = Tex.Sample(Smp, _Out.Uv.xy + float2(0, -SCDB.SprCutData.y));
    float4 ReturnResult = TexAdd.Sample(Smp, _Out.Uv.xy + Return.r * 0.25f);
    return ReturnResult;
}