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
		DirectX::XMMATRIX world; //�������
		DirectX::XMMATRIX worldInvTranspose;    //����任��ת�þ���
	};
	//�������
public:
	struct SufMaterial
	{
		DirectX::XMFLOAT4 ambient;
		DirectX::XMFLOAT4 diffuse;
		DirectX::XMFLOAT4 specular; // w = ���淴��ǿ��
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
	ComPtr<ID3D11Buffer> m_pTransformBuffer;             //�任����������
	ComPtr<ID3D11Buffer> m_pSufMatBuffer;                //������ʻ�����
	ComPtr<ID3D11ShaderResourceView> m_pTexture;		 // ����
	ComPtr<ID3D11SamplerState> m_pSamplerState;		     // ������״̬
	ComPtr<ID3D11RasterizerState> m_pRS;                 //��դ����״̬
	ComPtr<ID3D11BlendState> m_pBS;                      //���״̬

	//ComPtr<ID3DX11EffectTechnique> m_pEffecTechnique;

	Shader* m_pShader;
	TransformBuffer c_TransformBuffer;
	SufMaterial cBSufMat;

	DirectX::XMMATRIX m_World;

	//map<ID3DX11EffectVariable*, ShaderValue*> m_ShaderDataMap;
};

