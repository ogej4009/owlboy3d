#include "LightBase.hlsli"

struct Vtx3D_In
{
    float4 Pos : POSITION;
    float4 Uv : TEXCOORD;
};

struct Vtx3D_Out
{
    float4 Pos : SV_Position;
    float4 Uv : TEXCOORD;
};

Vtx3D_Out VS_DeferredLight(Vtx3D_In _In)
{
    Vtx3D_Out Out = (Vtx3D_Out) 0;
    Out.Pos = _In.Pos;
    Out.Uv = _In.Uv;
    return Out;
}

struct LightOut
{
    float4 DifColor : SV_Target0;
    float4 SpcColor : SV_Target1;
    float4 AmbColor : SV_Target2;
    float4 LightColor : SV_Target3;
};

cbuffer OneLightData : register(b5)
{
    LightData LData;
}

Texture2D PosTex : register(t0);
Texture2D NorTex : register(t1);
Texture2D ShadowTex : register(t2);
SamplerState Smp : register(s0);
SamplerState ShadowSmp : register(s1);

LightOut PS_DeferredLight(Vtx3D_Out _In)
{
    float4 Position = PosTex.Sample(Smp, _In.Uv.xy);

    if (0 >= Position.a)
    {
        clip(-1);
    }

    float4 Normal = NorTex.Sample(Smp, _In.Uv.xy);

    Position.w = 1.0f;
    Normal.w = 0.0f;

    CalLightResult LightColor = CalDirLight(Position, Normal, LData);
    LightOut Out = (LightOut) 0;
    Out.DifColor = LightColor.Dif;
    Out.SpcColor = LightColor.Spc;
    Out.AmbColor = LightColor.Amb;

    if (0 < Out.DifColor.x)
    {
        float4 vWorld = mul(float4(Position.xyz, 1.0f), LData.m_CamViewInverse);

        float4 vShadowProjPos = mul(vWorld, LData.m_ViewProj);
        float fDepth = vShadowProjPos.z / vShadowProjPos.w;

        float2 vShadowUv = float2((vShadowProjPos.x / vShadowProjPos.w) * 0.5f + 0.5f
        , (vShadowProjPos.y / vShadowProjPos.w) * -0.5f + 0.5f);

        if (0.001f < vShadowUv.x && 0.999f > vShadowUv.x &&
			0.001f < vShadowUv.y && 0.999f > vShadowUv.y)
        {
            float fShadowDepth = ShadowTex.Sample(ShadowSmp, vShadowUv.xy).r;

            if (0.0f < fShadowDepth && fDepth > fShadowDepth + 0.001f)
            {
                Out.DifColor *= 0.01f;
                Out.SpcColor = 0.0f;
            }
        }
    }

    Out.LightColor = Out.DifColor + Out.SpcColor + Out.AmbColor;

    return Out;
}