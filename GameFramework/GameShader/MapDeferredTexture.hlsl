#include "BumpBase.hlsli"

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

cbuffer MapOption : register(b3)
{
    float XCount;
    float ZCount;
    float PixelRatio;
    float YScale;
    float4 PixelUv;
    float4 PixelScale;
}

Texture2D WTex : register(t0);
SamplerState Smp : register(s0);

Vtx3D_Out VS_MapDeferredTexture(Vtx3D_In _In)
{
    float2 YValueUv = float2(_In.Uv.x / XCount, _In.Uv.y / ZCount);
    float2 RightUv = float2(YValueUv.x + PixelUv.x * PixelRatio, YValueUv.y);
    float2 ForwardUv = float2(YValueUv.x, YValueUv.y - PixelUv.y * PixelRatio);

    float4 MapColor = WTex.SampleLevel(Smp, YValueUv.xy, 0);
    float4 ColorRight = WTex.SampleLevel(Smp, RightUv.xy, 0);
    float4 ColorForward = WTex.SampleLevel(Smp, ForwardUv.xy, 0);

    float4 Pos = _In.Pos;
    float4 Right = float4(Pos.x + PixelScale.x * PixelRatio, 0.0f, Pos.z, 0.0f);
    float4 Forward = float4(Pos.x, 0.0f, Pos.z + PixelScale.y * PixelRatio, 0.0f);
   
    _In.Pos.y = MapColor.x;
    Pos.y = MapColor.x * YScale;
    Right.y = ColorRight.x * YScale;
    Forward.y = ColorForward.x * YScale;

    _In.Normal.xyz = normalize(cross(Forward.xyz - Pos.xyz, Right.xyz - Pos.xyz));

    Pos.w = 1.0f;
    _In.Normal.w = 0.0f;
    Vtx3D_Out Out = (Vtx3D_Out) 0;

    Out.Pos = mul(_In.Pos, WVP);
    Out.Uv = _In.Uv;
    Out.Color = _In.Color;
    Out.ViewPos = mul(_In.Pos, WV);
    Out.ViewNormal = normalize(mul(_In.Normal, WV));

    _In.BiNormal.w = 0.0f;
    Out.ViewBiNormal = normalize(mul(_In.BiNormal, WV));

    _In.Tangent.w = 0.0f;
    Out.ViewTangent = normalize(mul(_In.Tangent, WV));

    return Out;
}

struct DeferredOut
{
    float4 DifColor : SV_Target0;
    float4 PosColor : SV_Target1;
    float4 NorColor : SV_Target2;
    float4 DepColor : SV_Target3;
};

cbuffer RenderOption : register(b8)
{
    int IsDifTexture;
    int IsNormalTexture;
    int IsOutLine;
    int IsShadow;
    int IsAni;
    int IsDummy0;
    int IsDummy1;
    int IsDummy2;
    float4 BasicColor;
}

Texture2D BaseTex : register(t0);
Texture2D NormalTexture : register(t1);

DeferredOut PS_MapDeferredTexture(Vtx3D_Out _In)
{
    DeferredOut Out = (DeferredOut) 0;
    Out.DifColor = BaseTex.Sample(Smp, _In.Uv.xy);
    Out.NorColor = _In.ViewNormal;
    Out.PosColor = _In.ViewPos;
    Out.DepColor.x = _In.ViewPos.z;
    Out.DepColor.w = Out.PosColor.w = Out.NorColor.w = 1.0f;
    return Out;
}
