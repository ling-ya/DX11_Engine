#pragma once
#include "Component.h"
#include"DXTrace.h"
#include"Mesh.h"
#include"Material.h"
#include"Vertex.h"


class MeshRender : public Component
{
public:
	MeshRender(Mesh* pMesh);
	~MeshRender();
	virtual void Start();
	virtual void Update(float deltaTime);
	void SetVertexBuffer();
	void SetVertexLayout();
	void SetIndexBuffer();
public:
	//ComPtr<ID3DBlob> m_pBytecodeBlob;
	//ComPtr<ID3D11VertexShader> m_pVertexShader;
	ComPtr<ID3D11Buffer> m_pConstantBuffer;   //常量缓冲区
	//ComPtr<ID3D11PixelShader> m_pPixelShader;
	ComPtr<ID3D11Buffer> m_pVertexBuffer;				// 顶点缓冲区
	ComPtr<ID3D11Buffer> m_pIndexBuffer;				// 索引缓冲区
	ComPtr<ID3D11InputLayout> m_pVertexLayout;          //顶点输入布局
	Mesh* m_pMesh;
	Material* m_pMat;

public:
	UINT  stride;
	UINT offset;
	vector<D3D11_INPUT_ELEMENT_DESC> inputLayout;
	//ConstantBuffer cBuffer;
	//MeshData<VertexPosColor,DWORD> meshData;
};

