#pragma once
#include <GameMath.h>

struct LightData
{
    float4 DifColor;
    float4 SpcColor;
    float4 AmbColor;
    float4 LightPower;
    float4 SpecPow;
    float4 LightDir;
    float4 LightDirInv;
    float4 LightPos;
    float4 LightRange;
    float4 ShadowOption;
    float4 CamPos;
    float4 OnOff;
    float4 m_ShadowRange;
    CMatrix m_View;
    CMatrix m_Proj;
    CMatrix m_ViewProj;
    CMatrix m_CamViewInverse;

    LightData()
        : SpecPow(10000.0f, 0.0f, 0.0f, 0.0f)
        , LightPower(1.0f, 1.0f, 1.0f, 1.0f)
    {
    }

};

struct ObjectLightData
{
    int LightCount[4];
    LightData ArrLightData[128];
};

struct DebugOption
{

    bool IsTexture0;
    bool IsTexture1;
    bool IsTexture2;
    bool IsTexture3;

public:
    float Dumy1;
    float Dumy2;
    float Dumy3;
    float4 DebugDrawColor;

public:
    DebugOption()
    {
        memset(this, 0, sizeof(DebugOption));
    }
};
