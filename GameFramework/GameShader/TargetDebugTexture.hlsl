
struct Vtx2D_In
{
    float4 Pos : POSITION;
    float4 Uv : TEXCOORD;
};

struct VTx2D_Out
{
    float4 Pos : SV_Position;
    float4 Uv : TEXCOORD;
};

cbuffer WVP_Matrix : register(b0)
{
    matrix WVP;
}

VTx2D_Out VS_TargetDebugTexture(Vtx2D_In _In)
{
    VTx2D_Out Out = (VTx2D_Out) 0;
    Out.Pos = mul(_In.Pos, WVP);
    Out.Uv = _In.Uv;
    return Out;
}

Texture2D Tex : register(t0);
SamplerState Smp : register(s0);

float4 PS_TargetDebugTexture(VTx2D_Out _In) : SV_Target0
{
    float4 Color = Tex.Sample(Smp, _In.Uv.xy);
    return Color;
}