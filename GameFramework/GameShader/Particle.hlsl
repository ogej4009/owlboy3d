#include "RenderBase.hlsli"

struct VtxParticle_In
{
    float4 vPos : POSITION;
    uint iInstID : SV_InstanceID;
};

struct VtxParticle_Out
{
    float fInstID : FOG;
};

VtxParticle_Out VS_Particle(VtxParticle_In _input)
{
    VtxParticle_Out output = (VtxParticle_Out) 0.f;

    output.fInstID = (float) _input.iInstID;

    return output;
}

struct tParticle
{
    float4 vWorldPos;
    float4 vDir;
    float fSpeed;
    float fAddSpeed;
    float fMaxLifeTime;
    float fCurLifeTime;
    int4 iParticlePad;
    int iAlive;
    int iTemp1;
    int iTemp2;
    int iTemp3;
};

struct tParticleShared
{
    float4 vStartScale;
    float4 vEndScale;
    float4 vStartColor;
    float4 vEndColor;
    uint iSpawnCount;
    uint iCurCount;
    uint Temp0;
    uint Temp1;
};

StructuredBuffer<tParticle> arrParticle : register(t12);
StructuredBuffer<tParticleShared> ParticleShared : register(t13);

struct GS_ParticleOut
{
    float4 vPosition : SV_Position;
    float4 vColor : COLOR;
    float2 vUV : TEXCOORD;
};

static float4 g_arrLocal[4] =
{
    { -0.5f, 0.5f, 0.f, 0.f },
    { 0.5f, 0.5f, 0.f, 0.f },
    { 0.5f, -0.5f, 0.f, 0.f },
    { -0.5f, -0.5f, 0.f, 0.f }
};

cbuffer TransData : register(b0)
{
    TransDataBase MatrixData;
}

[maxvertexcount(6)]
void GS_Particle(point VtxParticle_Out _input[1], inout TriangleStream<GS_ParticleOut> OutputStream)
{
    uint iInstID = (uint) _input[0].fInstID;

    if (0 == arrParticle[iInstID].iAlive)
    {
        return;
    }

    GS_ParticleOut arrOut[4] =
    {
        (GS_ParticleOut) 0.f, (GS_ParticleOut) 0.f, (GS_ParticleOut) 0.f, (GS_ParticleOut) 0.f
    };

    arrOut[0].vUV = float2(0.f, 0.f);
    arrOut[1].vUV = float2(1.f, 0.f);
    arrOut[2].vUV = float2(1.f, 1.f);
    arrOut[3].vUV = float2(0.f, 1.f);

    // ī�޶� ���� ������ ���ֺ��� ���ؼ�, ��ƼŬ�� view ��ǥ�� ���� ���Ѵ�.
    float4 vViewPos = mul(float4(arrParticle[iInstID].vWorldPos.xyz, 1.f), MatrixData.VIEW);

    // ��ƼŬ�� ���� ũ�⸦ ���Ѵ�.
    float fRatio = arrParticle[iInstID].fCurLifeTime / arrParticle[iInstID].fMaxLifeTime;

    //float3 vCurScale = lerp(ParticleShared[iInstID].vStartScale.xyz, ParticleShared[iInstID].vEndScale.xyz, float3(fRatio, fRatio, fRatio));
    //float4 vColor = lerp(ParticleShared[iInstID].vStartColor, ParticleShared[iInstID].vEndColor, float4(fRatio, fRatio, fRatio, fRatio));

    float3 vCurScale = lerp(ParticleShared[iInstID].vStartScale.xyz, ParticleShared[iInstID].vEndScale.xyz, float3(1.0f, 1.0f, 1.0f));
    float4 vColor = lerp(ParticleShared[iInstID].vStartColor, ParticleShared[iInstID].vEndColor, float4(1.0f, 1.0f, 1.0f, 1.f));

    //float3 vCurScale = float3(1.0f, 1.0f, 1.0f);
   // float4 vColor = float4(1.0f, 1.0f, 1.0f, 1.0f);

    for (int i = 0; i < 4; ++i)
    {
        // View Space ���� Ȯ���� 4���� ��ġ�� ���Ѵ�.    
        arrOut[i].vPosition = float4(g_arrLocal[i].xyz  /* * vCurScale */ + vViewPos.xyz, 1.f);

        // ������ǥ ���Ѵ�.
        arrOut[i].vPosition = mul(arrOut[i].vPosition, MatrixData.PROJ);

        // �÷��� ����
        arrOut[i].vColor = vColor;
    }

    OutputStream.Append(arrOut[0]);
    OutputStream.Append(arrOut[1]);
    OutputStream.Append(arrOut[2]);
    OutputStream.RestartStrip();

    OutputStream.Append(arrOut[0]);
    OutputStream.Append(arrOut[2]);
    OutputStream.Append(arrOut[3]);
    OutputStream.RestartStrip();
}

Texture2D Tex : register(t0);
SamplerState Smp : register(s0);

float4 PS_Particle(GS_ParticleOut _input) : SV_Target
{
    float4 vTexColor = Tex.Sample(Smp, _input.vUV);

    if (vTexColor.x == 1.0f && vTexColor.y == 1.0f && vTexColor.z == 1.0f)
    {
        vTexColor.a = 0.0f;
    }

    return vTexColor;
}
