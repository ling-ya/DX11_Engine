#include "Light.h"
#include"Transform.h"
Light::Light():m_CBLight()
{

}

void Light::Start()
{
	//方向光
	m_CBLight.dirLight[0].ambient = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	m_CBLight.dirLight[0].diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	m_CBLight.dirLight[0].specular = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
	m_CBLight.dirLight[0].direction = XMFLOAT3(0.0f, -1.0f, 0.0f);
	// 点光
	m_CBLight.pointLight[0].position = XMFLOAT3(0.0f, 10.0f, 0.0f);
	m_CBLight.pointLight[0].ambient = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	m_CBLight.pointLight[0].diffuse = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
	m_CBLight.pointLight[0].specular = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	m_CBLight.pointLight[0].att = XMFLOAT3(0.0f, 0.1f, 0.0f);
	m_CBLight.pointLight[0].range = 25.0f;

	m_CBLight.numDirLight = 1;
	m_CBLight.numPointLight = 0;
	m_CBLight.numSpotLight = 0;
	m_CBLight.sysPos = XMFLOAT4(0.0f, 0.0f, -5.0f, 0.0f);;
	// 设置常量缓冲区描述
	D3D11_BUFFER_DESC cbd;
	ZeroMemory(&cbd, sizeof(cbd));
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	// 新建用于VS和PS的常量缓冲区
	cbd.ByteWidth = sizeof(CBLight);
	HR(Graphics::m_pDevice->CreateBuffer(&cbd, nullptr, m_pConstantBuffer.GetAddressOf()));

	D3D11_MAPPED_SUBRESOURCE mappedData;
	HR(Graphics::m_pContext->Map(m_pConstantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData));
	memcpy_s(mappedData.pData, sizeof(CBLight), &m_CBLight, sizeof(CBLight));
	Graphics::m_pContext->Unmap(m_pConstantBuffer.Get(), 0);
	Graphics::m_pContext->PSSetConstantBuffers(3, 1, m_pConstantBuffer.GetAddressOf());//灯光常量索引为3
}

void Light::Update(float deltaTime)
{
	DirectX::XMMATRIX w = m_pObject->GetComponent<Transform>()->GetWorldToLocalMatrixXM();
}
