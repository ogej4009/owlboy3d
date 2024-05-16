
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
    Matrix m_View;
    Matrix m_Proj;
    Matrix m_ViewProj;
    Matrix m_CamViewInverse;
};

struct CalLightResult
{
    float4 Dif;
    float4 Spc;
    float4 Amb;
};

CalLightResult CalDirLight(float4 _vViewPos, float4 _vViewNormal, LightData _Data)
{
    CalLightResult Result;
    Result.Dif.xyzw = max(0, dot(_vViewNormal.xyz, _Data.LightDirInv.xyz));

    float3 vR;
    float3 vE;

    vR = normalize(2.0f * _vViewNormal.xyz * dot(_Data.LightDirInv.xyz, _vViewNormal.xyz) - _Data.LightDirInv.xyz);
    vE = normalize(_Data.CamPos.xyz - _vViewPos.xyz);

    Result.Spc.x = max(0, dot(vR.xyz, vE.xyz));
    Result.Spc.xyzw = pow(Result.Spc.x, _Data.SpecPow.x);
    Result.Amb = _Data.AmbColor;
    Result.Dif *= _Data.LightPower.x * _Data.LightPower.w;
    Result.Spc *= _Data.LightPower.y * _Data.LightPower.w;
    Result.Amb *= _Data.LightPower.z * _Data.LightPower.w;
    
    return Result;
}

struct ObjectLightData
{
    int4 LightCount;
    LightData ArrLightData[128];
};