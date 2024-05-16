
struct VtxGrid_In
{
    float4 Pos : POSITION;
    float4 Uv : TEXCOORD;
    float4 Color : COLOR;
};

struct VtxGrid_Out
{
    float4 Pos : SV_Position;
    float4 WPos : POSITION; 
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

cbuffer XTransData : register(b0)
{
    float4 XT_POS;
    float XT_GRIDDIVIDE;
    float XT_GRIDAREA;
    float XT_GRIDMINALPHA;
    float XT_LINETHICKNESS;
}

VtxGrid_Out VS_Grid(VtxGrid_In _In)
{
    VtxGrid_Out Out = (VtxGrid_Out) 0;
    Out.Pos = mul(_In.Pos, WVP);
    Out.WPos = mul(_In.Pos, WWORLD);
    Out.Uv = _In.Uv;
    Out.Color = _In.Color;
    return Out;
}

float4 PS_Grid(VtxGrid_Out _In) : SV_Target0
{
    float Color = _In.Color;
    float4 Pos = _In.WPos;

    Pos.y = 0.0f;

    float Len = length(Pos - XT_POS);

    Color.r = XT_GRIDAREA / Len;
   
    if (0.05f > Color.r)
    {
        clip(-1);
    }

    float ModX = _In.WPos.x % XT_GRIDDIVIDE;
    float ModZ = _In.WPos.z % XT_GRIDDIVIDE;

    ModX = abs(ModX);
    ModZ = abs(ModZ);

    if (XT_LINETHICKNESS > ModX || XT_GRIDDIVIDE - XT_LINETHICKNESS < ModX)
    {
        return Color;
    }
    
    if (XT_LINETHICKNESS > ModZ || XT_GRIDDIVIDE - XT_LINETHICKNESS < ModZ)
    {
        return Color;
    }

    clip(-1);
    return _In.Color;
}