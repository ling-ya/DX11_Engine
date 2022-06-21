#include "LightHelper.hlsli"

Texture2D g_Tex : register(t0);
SamplerState g_Samliner : register(s0);

cbuffer TransformBuffer : register(b0)
{
    matrix g_World;
    //matrix g_View;
    //matrix g_Proj;
    matrix g_WorldInvTranspose;
    matrix g_Reflection;
    int g_IsReflection;
    float3 g_Pad1;
}

cbuffer VPBuffer : register(b1)
{
    matrix g_View;
    matrix g_Proj;
}


 cbuffer cBSufMat : register(b2)
 {
    float4 g_Matmbient;
    float4 g_Matdiffuse;
    float4 g_Matspceular;
    float4 g_Matreflect;
 }


 cbuffer cBLight : register(b3)
 {
    DirectionalLight g_DirLight[10];
    PointLight g_PointLight[10];
    SpotLight g_SpotLight[10];
    float4 g_sysPos;
 	int g_NumDirLight;
 	int g_NumPointLight;
 	int g_NumSpotLight;
 }


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

 
 void ComputeDirectionalLight(DirectionalLight L, float3 normal,float3 toEye,float4 g_matAmbient,float4 g_matDiffuse, float4 g_spec,out float4 ambient,out float4 diffuse, out float4 spec)
{
    //初始化输出
    ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
    diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
    spec = float4(0.0f, 0.0f, 0.0f, 0.0f);

    //光向量与照射方向相反
    float3 lightVec = -L.Direction;

    //添加环境光
    ambient = L.Ambient *g_matAmbient;

    // 添加漫反射光和镜面光
    float diffuseFactor = dot(lightVec, normal);

    //展开，避免动态分支
    [flatten]
    if(diffuseFactor >0.0f)
    {
        float3 v = reflect(-lightVec,normal);
        float specFactor = pow(max(dot(v,toEye),0.0f),g_spec.w);
        diffuse = diffuseFactor * g_matDiffuse * L.Diffuse;
        spec = specFactor *  g_spec * L.Specular;
    }
}

