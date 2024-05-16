
float4 CalBump(float4 _ViewNormal, float4 _BiNormal, float4 _Tangent, float2 _Uv, Texture2D _Bump, SamplerState _Smp)
{
    float4 TexNormal = _Bump.Sample(_Smp, _Uv.xy);
    
    TexNormal = TexNormal * 2.0f - 1.0f;
    TexNormal.w = 0.0f;
    TexNormal = normalize(TexNormal);

    float3x3 TangentSpace = float3x3(_Tangent.xyz, _BiNormal.xyz, _ViewNormal.xyz);
    TexNormal.xyz = mul(TexNormal.xyz, TangentSpace);
    TexNormal = normalize(TexNormal);

    return TexNormal;
}