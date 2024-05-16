
struct VtxTarget_In
{
    float4 Pos : POSITION;
    float4 Uv : TEXCOORD;
    float4 Color : COLOR;
    float4 Normal : NORMAL;
};

struct VtxTarget_Out
{
    float4 Pos : SV_Position;
    float4 Uv : TEXCOORD;
    float4 Color : COLOR;
    float4 Normal : NORMAL;
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

cbuffer MotionBlurData : register(b1)
{
    matrix Prev_WVP;
    matrix WVP2;
    float4 Prev_Pos;
    float4 Pos;
    float4 null;
    float4 null1;
}

// VS
VtxTarget_Out VS_MotionBlurDraw(VtxTarget_In _In)
{
    VtxTarget_Out Out = (VtxTarget_In) 0;
    Out.Pos = _In.Pos;
    Out.Uv = _In.Uv;
    Out.Color = _In.Color;
    Out.Normal = _In.Normal;
    return Out;
}

Texture2D Tex : register(t0);
SamplerState Smp : register(s0);

float4 PS_MotionBlurDraw(VtxTarget_Out _In) : SV_Target0
{
    int Blur = 30;
    float4 curP = mul(Pos, WVP2);
    float4 prevP = mul(Prev_Pos, Prev_WVP);
    curP.xyz /= curP.w;
    prevP.xyz /= prevP.w;
    float4 velocity = (curP - prevP);
    velocity.x *= 0.5f;
    velocity.y *= -0.5f;
    float4 RealColor = Tex.Sample(Smp, _In.Uv.xy);
    
    if (1 == RealColor.x && 0 == RealColor.y && 0 == RealColor.z)
    {
        clip(-1);
    }

    if (0 == RealColor.x && 0 == RealColor.y && 0 == RealColor.z)
    {
        clip(-1);
    }

    if (0 == velocity.x && 0 == velocity.y && 0 == velocity.z)
    {
        clip(-1);
    }

    int cnt = 1;
    float4 BColor;

    for (int i = cnt; i < Blur; i++)
    {

        BColor = Tex.Sample(Smp, _In.Uv.xy + velocity.xy * (float) i * 10);

        if (velocity.a < BColor.a + 0.04f)
        {
            cnt++;
            RealColor += BColor / (Blur * 2);
        }
    }
	
    RealColor.xyz -= 0.08f;
    RealColor.w = 1.0f;

    if (1 == RealColor.x)
    {
        clip(-1);
    }
	
    return RealColor;

}
