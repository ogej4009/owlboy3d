
struct Vtx2D_In
{
    float4 Pos : POSITION;
    float4 Uv : TEXCOORD;
    float4 Color : COLOR;
};

struct Vtx2D_Out
{
    float4 Pos : SV_Position;
    float4 Uv : TEXCOORD;
    float4 Color : COLOR;
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

Vtx2D_Out VS_UI(Vtx2D_In _In)
{
    Vtx2D_Out Out = (Vtx2D_Out) 0;
    Out.Pos = mul(_In.Pos, WVP);
    Out.Uv = _In.Uv;
    Out.Color = _In.Color;
    return Out;
}

Texture2D Tex : register(t0);
SamplerState Smp : register(s0);

float4 PS_UI(Vtx2D_Out _In) : SV_Target0
{
    float4 Color = Tex.Sample(Smp, _In.Uv.xy);
    return Color;
}
