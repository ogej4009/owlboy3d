
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

cbuffer Distance : register(b1)
{
    float4 Dis[4];
}

VtxTarget_Out VS_OutLineDraw(VtxTarget_In _In)
{
    VtxTarget_Out Out = (VtxTarget_In) 0;
    Out.Pos = _In.Pos;
    Out.Uv = _In.Uv;
    return Out;
}

cbuffer OUTLINEDATA : register(b0)
{
    float4 PixelUv[4];
    float4 LineColor;
}

Texture2D Tex : register(t0);
SamplerState Smp : register(s0);

float4 PS_OutLineDraw(VtxTarget_Out _In) : SV_Target0
{
    float limit = Dis[0];
    float4 TexColor = Tex.Sample(Smp, _In.Uv.xy);
	
    if (0 != TexColor.x)
    {
        clip(-1);
    }

    TexColor = Tex.Sample(Smp, (_In.Uv.xy + PixelUv[0].xy / limit));
    
    if (0 != TexColor.x)
    {
        return LineColor;
    }
    
    TexColor = Tex.Sample(Smp, (_In.Uv.xy + PixelUv[1].xy / limit));
    
    if (0 != TexColor.x)
    {
        return LineColor;
    }
    
    TexColor = Tex.Sample(Smp, (_In.Uv.xy + PixelUv[2].xy / limit));
    
    if (0 != TexColor.x)
    {
        return LineColor;
    }
    
    TexColor = Tex.Sample(Smp, (_In.Uv.xy + PixelUv[3].xy / limit));
    
    if (0 != TexColor.x)
    {
        return LineColor;
    }

    clip(-1);

    return LineColor;
}
