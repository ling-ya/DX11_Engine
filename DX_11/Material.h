#pragma once
#include<wrl/client.h>
#include<map>
#include"DXTrace.h"
//#include"VertexShader.h"
//#include"PixelShader.h"
#include"Shader.h"

using namespace std;
using namespace Microsoft::WRL;

enum  class ShaderValueType
{
	INT,
	FLOAT,
	VECTOR,
	VECTORARRAY,
	MATRIX,
	TEXTURE
};

class ShaderValue 
{
public:
	ShaderValue() = default;
	~ShaderValue() = default;
public:
	void* m_pData;

	int m_Size;
	ShaderValueType m_Type;
};

class Material
{
public:
	struct TransformBuffer
	{
		DirectX::XMMATRIX world; //世界矩阵
		DirectX::XMMATRIX worldInvTranspose;    //世界变换逆转置矩阵
	};
	//表面材质
public:
	struct SufMaterial
	{
		DirectX::XMFLOAT4 ambient;
		DirectX::XMFLOAT4 diffuse;
		DirectX::XMFLOAT4 specular; // w = 镜面反射强度
		DirectX::XMFLOAT4 reflect;
	};


public:
	Material(Shader* pShader);
	~Material() = default;
	void Update(float deltaTime);
	void SetInt(string name, int value);
	void SetFloat(string name, float value);
	void SetMatrix(string name, XMMATRIX matrix);
	void SetVector4(string name, XMFLOAT4 vector4);
	void SetTexture(string texturePath);
	void SetDiffuse(XMFLOAT4 diffsue);
	void SetSpecluar(XMFLOAT4 spec);
	void SetAmbient(XMFLOAT4 ambient);
public:
	ComPtr<ID3D11Buffer> m_pTransformBuffer;             //变换常量缓存区
	ComPtr<ID3D11Buffer> m_pSufMatBuffer;                //表面材质缓冲区
	ComPtr<ID3D11ShaderResourceView> m_pTexture;		 // 纹理
	ComPtr<ID3D11SamplerState> m_pSamplerState;		     // 采样器状态
	ComPtr<ID3D11RasterizerState> m_pRS;                 //光栅化器状态
	ComPtr<ID3D11BlendState> m_pBS;                      //混合状态

	//ComPtr<ID3DX11EffectTechnique> m_pEffecTechnique;

	Shader* m_pShader;
	TransformBuffer c_TransformBuffer;
	SufMaterial cBSufMat;

	DirectX::XMMATRIX m_World;

	//map<ID3DX11EffectVariable*, ShaderValue*> m_ShaderDataMap;
};

