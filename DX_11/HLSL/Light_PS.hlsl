#include "MyLight.hlsli"

float4 PS(v2f i) : SV_TARGET
{
	float4 texColor = g_Tex.Sample(g_Samliner,i.uv);
	clip(texColor.a - 0.1f);
	//标准化法线
	i.NormalW = normalize(i.NormalW);
	//顶点指向观察位置的向量
	float3 toEyeW = normalize(g_sysPos.xyz - i.PosW);

	//初始化
	float4 ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
    float4 diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
    float4 spec = float4(0.0f, 0.0f, 0.0f, 0.0f);

	float4 A = float4(0.0f, 0.0f, 0.0f, 0.0f);
    float4 D = float4(0.0f, 0.0f, 0.0f, 0.0f);
    float4 S = float4(0.0f, 0.0f, 0.0f, 0.0f);
	int a ;
	for (a = 0; a < g_NumDirLight; ++a)
    {
        ComputeDirectionalLight(g_DirLight[a], i.NormalW, toEyeW, g_Matmbient, g_Matdiffuse, g_Matspceular, A, D, S);
        ambient += A;
        diffuse += D;
        spec += S;
    }
	
	float4 finalColor = texColor * (ambient + diffuse) + spec;
	finalColor.a = texColor.a * g_Matdiffuse.a;
	return finalColor;
}