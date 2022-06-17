#include "Camera.h"
#include"Transform.h"

Camera::Camera() :m_bViewProjBuffer()//,m_pTrans(nullptr)
{

}

void Camera::Start()
{
	//m_bViewProjBuffer.view = XMMatrixTranspose(XMMatrixLookAtLH(
	//	XMVectorSet(0.0f, 0.0f, -5.0f, 0.0f),
	//	XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),
	//	XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)
	//));//先把矩阵转置
	//m_bViewProjBuffer.proj = XMMatrixTranspose(XMMatrixPerspectiveFovLH(m_FovY, m_Aspect, m_NearZ, m_FarZ));

	m_bViewProjBuffer.view = XMMatrixTranspose(GetViewXM());
	m_bViewProjBuffer.proj = XMMatrixTranspose(GetProjXM());

	//创建常量缓冲区
	D3D11_BUFFER_DESC cbd;
	ZeroMemory(&cbd, sizeof(cbd));
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.ByteWidth = sizeof(ViewProjBuffer);
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	// 新建常量缓冲区，不使用初始数据
	HR(Graphics::m_pDevice->CreateBuffer(&cbd, nullptr, m_pVPConstantBuffer.GetAddressOf()));

	Graphics::m_pContext->VSSetConstantBuffers(1, 1, m_pVPConstantBuffer.GetAddressOf());//VP矩阵索引为1

	D3D11_MAPPED_SUBRESOURCE mappedData;
	HR(Graphics::m_pContext->Map(m_pVPConstantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData));
	memcpy_s(mappedData.pData, sizeof(ViewProjBuffer), &m_bViewProjBuffer, sizeof(ViewProjBuffer));
	Graphics::m_pContext->Unmap(m_pVPConstantBuffer.Get(), 0);
}


XMMATRIX Camera::GetViewXM()const
{
	return m_pObject->GetComponent<Transform>()->GetWorldToLocalMatrixXM();
	//return m_pTrans->GetWorldToLocalMatrixXM();
}

XMMATRIX Camera::GetProjXM()const
{
	return XMMatrixPerspectiveFovLH(m_FovY, m_Aspect, m_NearZ, m_FarZ);
}


XMMATRIX Camera::GetViewProjXM()const
{
	return GetViewXM() * GetProjXM();
}


void Camera::Update(float deltaTime)
{
	m_bViewProjBuffer.view = XMMatrixTranspose(GetViewXM());
	m_bViewProjBuffer.proj = XMMatrixTranspose(GetProjXM());
	D3D11_MAPPED_SUBRESOURCE mappedData;
	HR(Graphics::m_pContext->Map(m_pVPConstantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData));
	memcpy_s(mappedData.pData, sizeof(ViewProjBuffer), &m_bViewProjBuffer, sizeof(ViewProjBuffer));
	Graphics::m_pContext->Unmap(m_pVPConstantBuffer.Get(), 0);
}

void Camera::SetFrustum(float fovY, float aspect, float nearZ, float farZ) 
{
	m_FovY = fovY;
	m_Aspect = aspect;
	m_NearZ = nearZ;
	m_FarZ = farZ;
}
