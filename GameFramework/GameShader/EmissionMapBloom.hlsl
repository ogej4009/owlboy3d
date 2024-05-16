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

VtxTarget_Out VS_EmissionMapBloom(VtxTarget_In _In)
{
    VtxTarget_Out Out = (VtxTarget_In) 0;
    Out.Pos = _In.Pos;
    Out.Uv = _In.Uv;
    return Out;
}

static float g_vFilter[25] =
{
    1.0F, 2.0f, 4.0f, 2.0f, 1.0f,
    2.0F, 4.0f, 8.0f, 4.0f, 2.0f,
    4.0F, 8.0f, 16.0f, 8.0f, 4.0f,
    2.0F, 4.0f, 8.0f, 4.0f, 2.0f,
    1.0F, 2.0f, 4.0f, 2.0f, 1.0f,
};

cbuffer TargetUvSize : register(b1)
{
    float4 SmallUvSize;
}

Texture2D SmallTex : register(t0);
SamplerState Smp : register(s0);

float4 PS_EmissionMapBloom(VtxTarget_Out _In) : SV_Target0
{
    float4 Sum;

    for (int y = 0; y < 5; ++y)
    {
        for (int x = 0; x < 5; ++x)
        {
            float2 Uv = _In.Uv.xy + float2((y - 2) * SmallUvSize.x, (x - 2) * SmallUvSize.y);
            Sum += SmallTex.Sample(Smp, Uv) * g_vFilter[y * 5 + x];
        }
    }

    Sum /= 100.0f;
    Sum.a = Sum.x;
    
    return Sum;
}
