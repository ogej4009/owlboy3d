
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

Vtx3D_Out VS_DeferredMerge(Vtx3D_In _In)
{
    Vtx3D_Out Out = (Vtx3D_Out) 0;
    Out.Pos = _In.Pos;
    Out.Uv = _In.Uv;
    return Out;
}

struct DeferredOut
{
    float4 DeferredColor : SV_Target0;
};

Texture2D DifColor : register(t0);
Texture2D LightColor : register(t1);
SamplerState Smp : register(s0);

DeferredOut PS_DeferredMerge(Vtx3D_Out _In)
{
    float4 DifOut = DifColor.Sample(Smp, _In.Uv.xy);

    if (0 >= DifOut.a)
    {
        clip(-1);
    }

    float4 DifLightOut = LightColor.Sample(Smp, _In.Uv.xy);

    DeferredOut Out = (DeferredOut) 0;
    Out.DeferredColor = DifOut;
    Out.DeferredColor.xyz *= DifLightOut.xyz;

    if (1 <= Out.DeferredColor.a)
    {
        Out.DeferredColor.a = 1.0f;
    }
    
    return Out;
}
