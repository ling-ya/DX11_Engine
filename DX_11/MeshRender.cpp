#include "MeshRender.h"
#include"Transform.h"
MeshRender::MeshRender(Mesh* pMesh) :m_pMesh(pMesh),m_pMat(nullptr), stride(sizeof(VertexPosNormalTangentTexColor)), offset(0)
{
}

MeshRender::~MeshRender()
{
}

void MeshRender::Start()
{
	SetVertexBuffer();
	SetIndexBuffer();
	SetVertexLayout();
}

void MeshRender::Update(float deltaTime)
{
	Graphics::m_pContext->RSSetState(m_pMat->m_pRS==nullptr?nullptr: m_pMat->m_pRS.Get());
	Graphics::m_pContext->OMSetBlendState(m_pMat->m_pBS == nullptr ? nullptr : m_pMat->m_pBS.Get(), nullptr, 0xFFFFFFFF);

	Graphics::m_pContext->IASetVertexBuffers(0, 1, m_pVertexBuffer.GetAddressOf(), &stride, &offset);
	Graphics::m_pContext->IASetIndexBuffer(m_pIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	Graphics::m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	Graphics::m_pContext->IASetInputLayout(m_pVertexLayout.Get());
	m_pMat->m_World = m_pObject->GetComponent<Transform>()->GetLocalToWorldMatrixXM();
	m_pMat->Update(deltaTime);


	//使用FX11框架
	//D3DX11_TECHNIQUE_DESC techDesc;
	//HR(m_pMat->m_pEffecTechnique->GetDesc(&techDesc));
	//for (UINT i = 0; i < techDesc.Passes; i++)
	//{
	//	m_pMat->m_pEffecTechnique->GetPassByIndex(i)->Apply(0, Graphics::m_pContext.Get());
	//	Graphics::m_pContext->DrawIndexed((UINT)m_pMesh->m_IndexList.size(), 0, 0);
	//}


	Graphics::m_pContext->DrawIndexed((UINT)m_pMesh->m_IndexList.size(), 0,0);
}

void MeshRender::SetVertexBuffer()
{
	vector<VertexPosNormalTangentTexColor> vertexdata;
	vertexdata.resize(m_pMesh->m_vertexCount);
	UINT byteWidth = 0;
	for (size_t i = 0; i < m_pMesh->m_vertexCount; i++)
	{
		UINT offest = 0;

		if (m_pMesh->m_verticesList.size() > 0) 
		{
			memcpy_s(reinterpret_cast<char*>(&vertexdata[i]) + offest, 12, reinterpret_cast<const char*>(&m_pMesh->m_verticesList[i]), 12);
		}
		offest += sizeof(XMFLOAT3);

		if (m_pMesh->m_vertiNormalList.size() > 0) 
		{
			memcpy_s(reinterpret_cast<char*>(&vertexdata[i]) + offest, 12, reinterpret_cast<const char*>(&m_pMesh->m_vertiNormalList[i]), 12);
		}
		offest += sizeof(XMFLOAT3);

		if (m_pMesh->m_vertTangentList.size() > 0)
		{
			memcpy_s(reinterpret_cast<char*>(&vertexdata[i]) + offest, 16, reinterpret_cast<const char*>(&m_pMesh->m_vertTangentList[i]), 16);
		}
		offest += sizeof(XMFLOAT4);

		if (m_pMesh->m_vectTexList.size() > 0)
		{
			memcpy_s(reinterpret_cast<char*>(&vertexdata[i]) + offest, 8, reinterpret_cast<const char*>(&m_pMesh->m_vectTexList[i]), 8);
		}
		offest += sizeof(XMFLOAT2);

		if (m_pMesh->m_vectColorList.size() > 0)
		{
			memcpy_s(reinterpret_cast<char*>(&vertexdata[i]) + offest, 16, reinterpret_cast<const char*>(&m_pMesh->m_vectColorList[i]), 16);
		}
	}


	m_pVertexBuffer.Reset();

	// 设置顶点缓冲区描述
	D3D11_BUFFER_DESC vbd;
	ZeroMemory(&vbd, sizeof(vbd));
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = stride * (UINT)vertexdata.size();
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	// 新建顶点缓冲区
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = vertexdata.data();
	HR(Graphics::m_pDevice->CreateBuffer(&vbd, &InitData, m_pVertexBuffer.GetAddressOf()));
}

void MeshRender::SetVertexLayout()
{
	HR(Graphics::m_pDevice->CreateInputLayout(VertexPosNormalTangentTexColor::inputLayout, ARRAYSIZE(VertexPosNormalTangentTexColor::inputLayout), m_pMat->m_pShader->GetByteCode()->GetBufferPointer(), m_pMat->m_pShader->GetByteCode()->GetBufferSize(), m_pVertexLayout.GetAddressOf()));

	//使用FX11框架
	//D3DX11_PASS_DESC passDesc;
	//HR(m_pMat->m_pEffecTechnique->GetPassByIndex(0)->GetDesc(&passDesc));
	//HR(Graphics::m_pDevice->CreateInputLayout(VertexPosNormalTangentTexColor::inputLayout, ARRAYSIZE(VertexPosNormalTangentTexColor::inputLayout), passDesc.pIAInputSignature, passDesc.IAInputSignatureSize, m_pVertexLayout.GetAddressOf()));
}

void MeshRender::SetIndexBuffer()
{
	//设置索引缓冲区描述
	D3D11_BUFFER_DESC ibd;
	ZeroMemory(&ibd, sizeof(ibd));
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = (UINT)m_pMesh->m_IndexList.size() *sizeof(UINT);
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;

	// 新建索引缓冲区
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = m_pMesh->m_IndexList.data();
	HR(Graphics::m_pDevice->CreateBuffer(&ibd, &InitData, m_pIndexBuffer.GetAddressOf()));
}

