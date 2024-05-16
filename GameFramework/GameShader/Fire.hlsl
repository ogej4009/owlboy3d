#include "LightBase.hlsli"
#include "AnimBase.hlsli"
#include "RenderBase.hlsli"

struct Vtx3D_Out
{
    float4 Pos : SV_Position;
    float4 Uv : TEXCOORD0;
    float4 UvCoords1 : TEXCOORD1;
    float4 UvCoords2 : TEXCOORD2;
    float4 UvCoords3 : TEXCOORD3;
    float4 Color : COLOR;
};

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

cbuffer TransData : register(b0)
{
    TransDataBase MatrixData;
}

cbuffer RenderOption : register(b1)
{
    RenderOptionBase RenderOptionData;
}

cbuffer CutBuffer : register(b3)
{
    float4 CutBuffer1;
    float4 CutBuffer2;
    float4 CutBuffer3;
};

Vtx3D_Out VS_Fire(BaseVtx_In _In)
{
    _In.Normal.w = 0.0f;

    Vtx3D_Out Out = (Vtx3D_Out) 0;
    Out.Pos = mul(_In.Pos, MatrixData.WVP);
    Out.Uv = _In.Uv;
    Out.Color = _In.Color;

    _In.Pos.w = 1.0f;

    Out.UvCoords1.x = CutBuffer1.x + CutBuffer1.z;
    Out.UvCoords1.y = CutBuffer1.y + CutBuffer1.w;

    Out.UvCoords2.x = CutBuffer2.x + CutBuffer2.z;
    Out.UvCoords2.y = CutBuffer2.y + CutBuffer2.w;

    Out.UvCoords3.x = CutBuffer3.x + CutBuffer3.z;
    Out.UvCoords3.y = CutBuffer3.y + CutBuffer3.w;

    return Out;
}

struct DeferredOut
{
    float4 DifColor : SV_Target0;
};

cbuffer DistortionBuffer : register(b4)
{
    float4 distortion12;
    float4 distortion3ScaleBias;
};

Texture2D noiseTexture : register(t0);
Texture2D fireTexture : register(t1);
SamplerState Smp : register(s0);
SamplerState Smp2 : register(s1);

DeferredOut PS_Fire(Vtx3D_Out _In)
{
    float4 noise1;
    float4 noise2;
    float4 noise3;
    float4 finalNoise;
    float perturb;
    float2 noiseCoords;
    float4 fireColor;
    float4 alphaColor;

    noise1 = noiseTexture.Sample(Smp, _In.UvCoords1.xy);
    noise2 = noiseTexture.Sample(Smp, _In.UvCoords2.xy);
    noise3 = noiseTexture.Sample(Smp, _In.UvCoords3.xy);

    noise1 = (noise1 - 0.5f) * 2.0f;
    noise2 = (noise2 - 0.5f) * 2.0f;
    noise3 = (noise3 - 0.5f) * 2.0f;

    noise1.xy = noise1.xy * distortion12.xy;
    noise2.xy = noise2.xy * distortion12.zw;
    noise3.xy = noise3.xy * distortion3ScaleBias.xy;

    finalNoise = noise1 + noise2;

    perturb = ((1.0f - _In.Uv.y) * distortion3ScaleBias.z) + distortion3ScaleBias.w;

    noiseCoords.xy = (finalNoise.xy * perturb) + _In.Uv.xy;

    fireColor = fireTexture.Sample(Smp2, noiseCoords.xy);

    DeferredOut Out;
    Out.DifColor.xyz = fireColor.xyz;
    Out.DifColor.a = 1.0f;
    return Out;
}
