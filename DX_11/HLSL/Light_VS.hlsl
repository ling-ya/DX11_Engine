#include "MyLight.hlsli"

v2f VS(a2v vIn)
{
	v2f o;
	matrix MATRXI_VP= mul(g_View,g_Proj);//先计算出VP矩阵
	float4 posW = mul(float4(vIn.PosL,1.0f),g_World); // 计算世界空间中的顶点位置
	float3 NormalW = mul(vIn.NormalL,(float3x3)g_WorldInvTranspose);  //将法线变换到世界空间中

	[flatten]
	if(g_IsReflection)
	{
		posW = mul(posW,g_Reflection);
		NormalW = mul(NormalW,(float3x3)g_Reflection);
	}

	o.PosH = mul(posW,MATRXI_VP);
	o.PosW = posW.xyz;
	o.NormalW = NormalW;
	o.uv = vIn.uv; 
	return o;
}