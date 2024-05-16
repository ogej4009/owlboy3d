#include "AnimBase.hlsli"
#include "RenderBase.hlsli"

struct VtxTarget_In
{
    float4 Pos : POSITION;
    float4 Uv : TEXCOORD;
};

struct VtxTarget_Out
{
    float4 Pos : SV_Position;
    float4 Uv : TEXCOORD;
};

VtxTarget_Out VS_EmissionMapBloomCheck(VtxTarget_In _In)
{
    VtxTarget_Out Out = (VtxTarget_In) 0;
    Out.Pos = _In.Pos;
    Out.Uv = _In.Uv;
    return Out;
}

Texture2D EmissionTex : register(t0);
Texture2D LightTex : register(t1);
SamplerState Smp : register(s0);

float4 PS_EmissionMapBloomCheck(VtxTarget_Out _In) : SV_Target0
{
    float4 EColor = EmissionTex.Sample(Smp, _In.Uv.xy);

    if (0 == EColor.x)
    {
        clip(-1);
    }

    return LightTex.Sample(Smp, _In.Uv.xy);
}
