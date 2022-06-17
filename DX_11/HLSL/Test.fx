float4x4 g_World;
float4x4 g_WorldIT;
float4x4 g_View;
float4x4 g_Proj;

//顶点输入结构
struct a2v 
{
    float3 PosL : POSITION;
    float3 NormalL : NORMAL;
    float2 uv : TEXCOORD;
};

struct v2f 
{
    float4 PosH : SV_POSITION;
    float3 PosW : POSITION;
    float3 NormalW : NORMAL;
    float2 uv : TEXCOORD;
};

v2f RenderSceneVS(a2v vIn)
{
    v2f o;
    float4x4 MATRIX_VP = mul(g_View, g_Proj);
    float4 posW = mul(float4(vIn.PosL, 1.0f), g_World); //转换到世界空间
    o.PosH = mul(posW,MATRIX_VP);
    o.PosW = posW.xyz;
    o.NormalW = mul(vIn.NormalL,(float3x3)g_WorldIT);
    o.uv = vIn.uv;
    return o;
}

float4 RenderScenePS(v2f i):SV_Target
{
    return float4(1.0,0.0,0.0,1.0);
}

technique11 FX_Main_11
{
    pass P0
    {
        SetVertexShader(CompileShader(vs_4_0_level_9_1, RenderSceneVS()));
        SetGeometryShader(NULL);
        SetPixelShader(CompileShader(ps_4_0_level_9_1, RenderScenePS()));
    }
}