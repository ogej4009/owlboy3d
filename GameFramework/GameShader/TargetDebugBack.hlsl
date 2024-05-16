
struct Vtx2D_In
{
    float4 Pos : POSITION;
};

struct Vtx2D_Out
{
    float4 Pos : SV_Position;
};

cbuffer WVP_Matrix : register(b0)
{
    matrix WVP;
}

Vtx2D_Out VS_TargetDebugBack(Vtx2D_In _In)
{
    Vtx2D_Out Out = (Vtx2D_Out) 0;
    Out.Pos = mul(_In.Pos, WVP);
    return Out;
}

cbuffer BackColor : register(b8)
{
    float4 DrawColor;
}

float4 PS_TargetDebugBack(Vtx2D_Out _In) : SV_Target0
{
    return DrawColor;
}