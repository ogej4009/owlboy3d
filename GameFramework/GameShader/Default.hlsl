#include "RenderBase.hlsli"

struct VtxIn
{
    float4 Pos : POSITION; 
    float4 Uv : TEXCOORD;
    float4 Color : COLOR;
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

VtxOut VS_Default(VtxIn _In)
{
    VtxOut Out = (VtxOut) 0;
    Out.Pos = mul(_In.Pos, TDB.WVP);
    Out.Uv = _In.Uv;
    Out.Color = _In.Color;
    float XSize = SCDB.SprCutData.z;
    float YSize = SCDB.SprCutData.w;
    float XStart = SCDB.SprCutData.x;
    float YStart = SCDB.SprCutData.y;
    Out.Uv.x = (Out.Uv.x * XSize) + XStart;
    Out.Uv.y = (Out.Uv.y * YSize) + YStart;
    return Out;
}

cbuffer DrawColor : register(b0) 
{
    float4 Color; 
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

DeferredOut PS_Default(VtxOut _Out) : SV_Target0
{
   //NormalOut Out;
   //Out.NormalColor = Tex.Sample(Smp, _Out.Uv.xy);
   //if (Option.x == 0)
   //{
   //    Out.NormalColor.xyz *= Color.xyz;
   //    Out.NormalColor.a *= Color.a;
   //}
   //else
   //{
   //    if (Out.NormalColor.x != 0 || Out.NormalColor.y != 0 || Out.NormalColor.z != 0)
   //    {
   
   //        Out.NormalColor.xyz = Color.xyz;
   //        Out.NormalColor.a = Color.a;
   //    }
   //}
   
    DeferredOut Out = (DeferredOut) 0;

    Out.DifColor = Tex.Sample(Smp, _Out.Uv.xy);

    Out.PosColor.x = 0.5f;
    Out.PosColor.y = 0.5f;
    Out.PosColor.z = 0.5f;

    Out.NorColor.x = 0.5f;
    Out.NorColor.y = 0.5f;
    Out.NorColor.z = 0.5f;

    Out.DepColor.x = 0.5f;
    Out.DepColor.y = 0.5f;
    Out.DepColor.z = 0.5f;
    
    // 1, 1, 1 * 1, 0, 0 == 1, 1, 1
    Out.DifColor.xyz *= Color.xyz;
    
    if (0 != Out.DifColor.a)
    {
        Out.DifColor.a = Color.a;
    }


    return Out;
   
}

/*
float4 PS_Frame(Vtx2D_Out _In) : SV_Target0
{
    float4 Color = Tex.Sample(Smp, _In.Uv.xy);
    float4 RedColor = { 1.0f, 0.0f, 0.0f, 1.0f };
   
    if (_In.Uv.x <= 0.01 || _In.Uv.x >= 0.99)
    {
        int a = 0;
        return RedColor;     
    }

    if (_In.Uv.y <= 0.01 || _In.Uv.y >= 0.99)
    {
        int a = 0;
        return RedColor;
    }
    
    Color.xyz *= RenderColor.xyz;
    
    if (0 != Color.a)
    {
        Color.a = RenderColor.a;
    }
  
    return Color;
}

*/
