#include "Material.h"
#include"DDSTextureLoader.h"
#include"WICTextureLoader.h"
using namespace DirectX;

Material::Material(Shader* pShader):m_pShader(pShader),c_TransformBuffer(), cBSufMat(), m_World()
{
	c_TransformBuffer.world = XMMatrixIdentity();
	c_TransformBuffer.worldInvTranspose= XMMatrixIdentity();
	c_TransformBuffer.reflection = XMMatrixTranspose(XMMatrixReflect(XMVectorSet(0.0f, 0.0f, -1.0f, 9.99f)));;

	cBSufMat.ambient = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	cBSufMat.diffuse = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
	cBSufMat.specular = XMFLOAT4(0.8f, 0.8f, 0.8f, 16.0f);


	//创建常量缓冲区
	D3D11_BUFFER_DESC cbd;
	ZeroMemory(&cbd, sizeof(cbd));
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.ByteWidth = sizeof(TransformBuffer);
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	// 新建常量缓冲区，不使用初始数据
	HR(Graphics::m_pDevice->CreateBuffer(&cbd, nullptr, m_pTransformBuffer.GetAddressOf()));

	cbd.ByteWidth = sizeof(SufMaterial);
	HR(Graphics::m_pDevice->CreateBuffer(&cbd, nullptr, m_pSufMatBuffer.GetAddressOf()));
	//D3D11_MAPPED_SUBRESOURCE mappedData;
	//HR(Graphics::m_pContext->Map(m_pSufMatBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData));
	//memcpy_s(mappedData.pData, sizeof(SufMaterial), &cBSufMat, sizeof(SufMaterial));
	//Graphics::m_pContext->Unmap(m_pSufMatBuffer.Get(), 0);
	//Graphics::m_pContext->PSSetConstantBuffers(2, 1, m_pSufMatBuffer.GetAddressOf());//材质表面索引为2


	// 初始化采样器状态
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	HR(Graphics::m_pDevice->CreateSamplerState(&sampDesc, m_pSamplerState.GetAddressOf()));


	//使用FX11框架
	//m_pEffecTechnique = m_pShader->m_pEffect->GetTechniqueByName("FX_Main_11");

}

void Material::Update(float deltaTime)
{
	c_TransformBuffer.world = XMMatrixTranspose(m_World);//先把矩阵转置
	c_TransformBuffer.worldInvTranspose = XMMatrixTranspose(InverseTranspose(m_World));//先逆转置矩阵，再转置


	Graphics::m_pContext->VSSetShader(m_pShader->m_pVertexShader.Get(),nullptr,0);

	D3D11_MAPPED_SUBRESOURCE mappedData;

	HR(Graphics::m_pContext->Map(m_pSufMatBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData));
	memcpy_s(mappedData.pData, sizeof(SufMaterial), &cBSufMat, sizeof(SufMaterial));
	Graphics::m_pContext->Unmap(m_pSufMatBuffer.Get(), 0);
	Graphics::m_pContext->PSSetConstantBuffers(2, 1, m_pSufMatBuffer.GetAddressOf());//材质表面索引为2


	HR(Graphics::m_pContext->Map(m_pTransformBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData));
	memcpy_s(mappedData.pData, sizeof(TransformBuffer), &c_TransformBuffer, sizeof(TransformBuffer));
	Graphics::m_pContext->Unmap(m_pTransformBuffer.Get(), 0);
	Graphics::m_pContext->VSSetConstantBuffers(0, 1, m_pTransformBuffer.GetAddressOf()); //世界变换常量索引为0


	Graphics::m_pContext->PSSetShader(m_pShader->m_pPixelShader.Get(), nullptr, 0);
	Graphics::m_pContext->PSSetSamplers(0, 1, m_pSamplerState.GetAddressOf());
	if (m_pTexture != nullptr) 
	{
		Graphics::m_pContext->PSSetShaderResources(0, 1, m_pTexture.GetAddressOf());
	}

	//if (m_pRS != nullptr)
	//{
	//	Graphics::m_pContext->RSSetState(m_pRS.Get());
	//}
	//else
	//{
	//	Graphics::m_pContext->RSSetState(nullptr);
	//}

	//if (m_pBS != nullptr)
	//{
	//	Graphics::m_pContext->OMSetBlendState(m_pBS.Get(),nullptr, 0xFFFFFFFF);
	//}
	//else
	//{
	//	Graphics::m_pContext->OMSetBlendState(nullptr, nullptr, 0xFFFFFFFF);
	//}

	//使用FX11框架

	//SetMatrix("g_World", m_World);
	//SetMatrix("g_WorldIT", InverseTranspose(m_World));//逆转置矩阵

	//for (map<ID3DX11EffectVariable*, ShaderValue*> ::iterator iter=m_ShaderDataMap.begin(); iter!=m_ShaderDataMap.end(); iter++)
	//{
	//	switch (iter->second->m_Type)
	//	{

	//	case ShaderValueType::INT:
	//	{
	//		ID3DX11EffectScalarVariable* pIntVar = iter->first->AsScalar();
	//		pIntVar->SetInt(*reinterpret_cast<int*>(iter->second->m_pData));//先转换成int* ，再取值;
	//	}
	//	break;

	//	case ShaderValueType::FLOAT:
	//	{
	//		ID3DX11EffectScalarVariable* pFloatVar = iter->first->AsScalar();
	//		pFloatVar->SetFloat(*reinterpret_cast<float*>(iter->second->m_pData));
	//	}
	//	break;

	//	case ShaderValueType::VECTOR:
	//	{
	//		ID3DX11EffectVectorVariable* pVectorVar = iter->first->AsVector();
	//		pVectorVar->SetFloatVector(reinterpret_cast<float*>(iter->second->m_pData));
	//	}
	//	break;

	//	case ShaderValueType::MATRIX:
	//	{
	//		ID3DX11EffectMatrixVariable* pMatrixVar = iter->first->AsMatrix();
	//		pMatrixVar->SetMatrix(reinterpret_cast<float*>(iter->second->m_pData));
	//	}
	//	break;

	//	case ShaderValueType::TEXTURE:
	//	{
	//		ID3DX11EffectShaderResourceVariable* pTexVar = iter->first->AsShaderResource();
	//		pTexVar->SetResource(reinterpret_cast<ID3D11ShaderResourceView*>(iter->second->m_pData));
	//	}
	//	break;
	//	}
	//}

}

void Material::SetInt(string name, int value)
{
	/*if (m_pShader != nullptr)
	{
		ID3DX11EffectVariable* pIntVariable = m_pShader->m_pEffect->GetVariableByName(name.c_str());
		if (pIntVariable != nullptr)
		{
			if (m_ShaderDataMap[pIntVariable] != nullptr)
			{
				delete m_ShaderDataMap[pIntVariable];
			}

			ShaderValue* m_pShaderValue = new ShaderValue;
			m_pShaderValue->m_pData = new int(value);
			m_pShaderValue->m_Type = ShaderValueType::INT;
			m_ShaderDataMap[pIntVariable] = m_pShaderValue;
		}
	}*/
}

void Material::SetFloat(string name, float value)
{
	//if (m_pShader != nullptr)
	//{
	//	ID3DX11EffectVariable* pIntVariable = m_pShader->m_pEffect->GetVariableByName(name.c_str());
	//	if (pIntVariable != nullptr)
	//	{
	//		if (m_ShaderDataMap[pIntVariable] != nullptr)
	//		{
	//			delete m_ShaderDataMap[pIntVariable];
	//		}

	//		ShaderValue* m_pShaderValue = new ShaderValue;
	//		m_pShaderValue->m_pData = new float(value);
	//		m_pShaderValue->m_Type = ShaderValueType::FLOAT;
	//		m_ShaderDataMap[pIntVariable] = m_pShaderValue;
	//	}
	//}
}

void Material::SetMatrix(string name, XMMATRIX matrix)
{
	//if (m_pShader != nullptr)
	//{
	//	ID3DX11EffectVariable* pIntVariable = m_pShader->m_pEffect->GetVariableByName(name.c_str());
	//	if (pIntVariable != nullptr)
	//	{
	//		if (m_ShaderDataMap[pIntVariable] != nullptr)
	//		{
	//			delete m_ShaderDataMap[pIntVariable];
	//		}

	//		ShaderValue* m_pShaderValue = new ShaderValue;
	//		m_pShaderValue->m_pData = new XMMATRIX(matrix);
	//		m_pShaderValue->m_Type = ShaderValueType::MATRIX;
	//		m_ShaderDataMap[pIntVariable] = m_pShaderValue;
	//	}
	//}
}

void Material::SetVector4(string name, XMFLOAT4 vector4)
{
	//if (m_pShader != nullptr)
	//{
	//	ID3DX11EffectVariable* pIntVariable = m_pShader->m_pEffect->GetVariableByName(name.c_str());
	//	if (pIntVariable != nullptr)
	//	{
	//		if (m_ShaderDataMap[pIntVariable] != nullptr)
	//		{
	//			delete m_ShaderDataMap[pIntVariable];
	//		}

	//		ShaderValue* m_pShaderValue = new ShaderValue;
	//		m_pShaderValue->m_pData = new XMFLOAT4(vector4);
	//		m_pShaderValue->m_Type = ShaderValueType::VECTOR;
	//		m_ShaderDataMap[pIntVariable] = m_pShaderValue;
	//	}
	//}
}

void Material::SetTexture(string texturePath)
{
	//ComPtr<ID3D11ShaderResourceView> m_texute;

	wstring path = StringConvert::StringToWString(texturePath);
	HR(CreateDDSTextureFromFile(Graphics::m_pDevice.Get(), path.c_str(), nullptr, m_pTexture.GetAddressOf()));

	//if (m_pShader != nullptr)
	//{
	//	ID3DX11EffectVariable* pIntVariable = m_pShader->m_pEffect->GetVariableByName(name.c_str());
	//	if (pIntVariable != nullptr)
	//	{
	//		if (m_ShaderDataMap[pIntVariable] != nullptr)
	//		{
	//			delete m_ShaderDataMap[pIntVariable];
	//		}
	//		ShaderValue* m_pShaderValue = new ShaderValue;
	//		m_pShaderValue->m_pData = m_texute.Get();
	//		m_pShaderValue->m_Type = ShaderValueType::TEXTURE;
	//		m_ShaderDataMap[pIntVariable] = m_pShaderValue;
	//	}
	//}
}

void Material::SetDiffuse(XMFLOAT4 diffsue)
{
	cBSufMat.diffuse = diffsue;
}

void Material::SetSpecluar(XMFLOAT4 spec)
{
	cBSufMat.specular = spec;
}

void Material::SetAmbient(XMFLOAT4 ambient)
{
	cBSufMat.ambient = ambient;
}


