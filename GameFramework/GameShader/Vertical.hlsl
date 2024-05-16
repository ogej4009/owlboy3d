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


VtxOut VS_Vertical(VtxIn _In)
{
    VtxOut Out = (VtxOut) 0;
    Out.Pos = mul(_In.Pos, TDB.WVP);
    Out.Uv = _In.Uv;
    Out.Color = _In.Color;
    float XSize = SCDB.SprCutData.z;
    float YSize = SCDB.SprCutData.w;
    float XStart = SCDB.SprCutData.x;
    float YStart = SCDB.SprCutData.y;
    Out.Uv.x = Out.Uv.x;
    Out.Uv.y = Out.Uv.y * SCDB.SprCutData.x - SCDB.SprCutData.y;
    return Out;
}

cbuffer DrawColor : register(b0)
{
    float4 Color; 
}

cbuffer RenderOption : register(b1)
{
    int4 Option;
}

Texture2D Tex : register(t0);
SamplerState Smp : register(s0);

float4 PS_Vertical(VtxOut _In) : SV_Target0
{
    float4 ReturnColor = Tex.Sample(Smp, _In.Uv.xy);

    if (Option.x == 0)
    {
        ReturnColor.xyz *= Color.xyz;
        ReturnColor.a *= Color.a;
    }
    else
    {
        if (ReturnColor.x != 0 || ReturnColor.y != 0 || ReturnColor.z != 0)
        {
            ReturnColor.xyz = Color.xyz;
            ReturnColor.a = Color.a;
        }
    }
 
    return ReturnColor;
}
