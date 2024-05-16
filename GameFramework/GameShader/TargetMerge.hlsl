
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

VtxTarget_Out VS_TargetMerge(VtxTarget_In _In)
{    
    VtxTarget_Out Out = (VtxTarget_In) 0;
    Out.Pos = _In.Pos;
    Out.Uv = _In.Uv;
    return Out;
}

cbuffer MergeOption : register(b0)
{
    float AlphaOption;
    float Dummy01;
    float Dummy02;
    float Dummy03;
}

Texture2D TargetTex : register(t0);
SamplerState Smp : register(s0);

float4 PS_TargetMerge(VtxTarget_Out _In) : SV_Target0
{
    float4 Color = TargetTex.Sample(Smp, _In.Uv.xy);

    if (Color.r >= 1.0f)
    {
        Color.r = 1.0f;
    }

    if (Color.g >= 1.0f)
    {
        Color.g = 1.0f;
    }

    if (Color.b >= 1.0f)
    {
        Color.b = 1.0f;
    }
    
    if (0 == AlphaOption)
    {
        if (1.0f < Color.a)
        {
            Color.a = 1.0f;
        }
    }
    else
    {
        if (1.0f < Color.a)
        {
            Color.a = Color.x;
        }
    }

    return Color;
}
