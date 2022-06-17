#include "Cube.hlsli"

// ������ɫ��
VertexOut VS(VertexIn vIn)
{
    VertexOut vOut;
    vOut.posH = mul(float4(vIn.pos, 1.0f),g_World);
    vOut.posH = mul( vOut.posH,g_View);
    vOut.posH = mul( vOut.posH,g_Proj);
    vOut.color = vIn.color; // ����alphaͨ����ֵĬ��Ϊ1.0
    return vOut;
}