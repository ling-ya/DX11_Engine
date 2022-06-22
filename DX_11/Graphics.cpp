#include "Graphics.h"
#include "ObjectManager.h"
#include "RenderStates.h"
ComPtr<ID3D11Device> Graphics::m_pDevice = nullptr;
ComPtr<ID3D11DeviceContext> Graphics::m_pContext = nullptr;

//const D3D11_INPUT_ELEMENT_DESC Graphics::VertexPosColor::inputLayout[2] = {
//	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//	{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
//};

/// <summary>
/// 在构造函数中初始化D3D
/// </summary>
Graphics::Graphics(HWND hwnd,UINT width,UINT height):m_Hwnd(hwnd)
{
	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 0;
	sd.BufferDesc.RefreshRate.Denominator = 0;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.SampleDesc.Count = 4;
	sd.SampleDesc.Quality = 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = hwnd;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;
	D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&sd,
		m_SwapChain.GetAddressOf(),
		m_pDevice.GetAddressOf(),
		nullptr,
		m_pContext.GetAddressOf());

	ComPtr<ID3D11Resource> pBackBuffer;
	m_SwapChain->GetBuffer(0, __uuidof(ID3D11Resource), reinterpret_cast<void**>(pBackBuffer.GetAddressOf()));
	m_pDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, m_pRenderTarget.GetAddressOf());

	////创建深度模板状态
	//D3D11_DEPTH_STENCIL_DESC dsDesc = {};
	//dsDesc.DepthEnable = TRUE;
	//dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	//dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
	//ComPtr<ID3D11DepthStencilState> pDSState;
	//HR(m_pDevice->CreateDepthStencilState(&dsDesc, pDSState.GetAddressOf()));
	////绑定深度模板状态
	//m_pContext->OMSetDepthStencilState(pDSState.Get(), 1u);

	//创建深度模板纹理
	D3D11_TEXTURE2D_DESC descDepth = {};
	descDepth.Width = width;
	descDepth.Height = height;
	descDepth.MipLevels = 1u;
	descDepth.ArraySize = 1u;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDepth.SampleDesc.Count = 4u;
	descDepth.SampleDesc.Quality = 0u;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	HR(m_pDevice->CreateTexture2D(&descDepth, nullptr, m_pDepthStencilBuffer.GetAddressOf()));

	//创建深度纹理视图
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
	descDSV.Format = DXGI_FORMAT_D32_FLOAT;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0u;
	//HR(m_pDevice->CreateDepthStencilView(m_pDepthStencilBuffer.Get(), &descDSV, m_pDepthStencilView.GetAddressOf()));
	HR(m_pDevice->CreateDepthStencilView(m_pDepthStencilBuffer.Get(), nullptr, m_pDepthStencilView.GetAddressOf()));//4倍抗锯齿

	m_pContext->OMSetRenderTargets(1, m_pRenderTarget.GetAddressOf(), m_pDepthStencilView.Get());


	m_ScreenViewport.TopLeftX = 0;
	m_ScreenViewport.TopLeftY = 0;
	m_ScreenViewport.Width = static_cast<float>(width);
	m_ScreenViewport.Height = static_cast<float>(height);
	m_ScreenViewport.MinDepth = 0.0f;
	m_ScreenViewport.MaxDepth = 1.0f;
	m_pContext->RSSetViewports(1, &m_ScreenViewport);

	RenderStates::InitAll(m_pDevice.Get());
}

//void Graphics::Init(int ClientWidth, int ClientHeight)
//{
	//HRESULT hr;
//	DXGI_SWAP_CHAIN_DESC sd = {};
//	sd.BufferDesc.Width = ClientWidth;
//	sd.BufferDesc.Height = ClientHeight;
//	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
//	sd.BufferDesc.RefreshRate.Numerator = 0;
//	sd.BufferDesc.RefreshRate.Denominator = 0;
//	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
//	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
//	sd.SampleDesc.Count = 1;
//	sd.SampleDesc.Quality = 0;
//	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
//	sd.BufferCount = 1;
//	sd.OutputWindow = m_Hwnd;
//	sd.Windowed = TRUE;
//	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
//	sd.Flags = 0;
//
//	UINT swapCreateFlags = 0u;
//#ifndef NDEBUG
//	swapCreateFlags |= D3D11_CREATE_DEVICE_DEBUG;
//#endif 
//
//	HR(D3D11CreateDeviceAndSwapChain(
//		nullptr,
//		D3D_DRIVER_TYPE_HARDWARE,
//		nullptr,
//		swapCreateFlags,
//		nullptr,
//		0,
//		D3D11_SDK_VERSION,
//		&sd,
//		m_SwapChain.GetAddressOf(),
//		m_pDevice.GetAddressOf(),
//		nullptr,
//		m_pContext.GetAddressOf()));
//	//if (FAILED(hr))
//	//{
//	//	MessageBox(0, L"D3D11CreateDevice Failed.", 0, 0);
//	//	return;
//	//}
//
//	ComPtr<ID3D11Resource> pBackBuffer;
//	HR(m_SwapChain->GetBuffer(0, __uuidof(ID3D11Resource), &pBackBuffer));
//	HR(m_pDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, m_pRenderTarget.GetAddressOf()));
//
//	//创建深度模板状态
//	D3D11_DEPTH_STENCIL_DESC dsDesc = {};
//	dsDesc.DepthEnable = TRUE;
//	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
//	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
//	ComPtr<ID3D11DepthStencilState> pDSState;
//	HR(m_pDevice->CreateDepthStencilState(&dsDesc, pDSState.GetAddressOf()));
//	//绑定深度模板状态
//	m_pContext->OMSetDepthStencilState(pDSState.Get(), 1u);
//
//	//创建深度模板纹理
//	D3D11_TEXTURE2D_DESC descDepth = {};
//	descDepth.Width = ClientWidth;
//	descDepth.Height = ClientHeight;
//	descDepth.MipLevels = 1u;
//	descDepth.ArraySize = 1u;
//	descDepth.Format = DXGI_FORMAT_D32_FLOAT;
//	descDepth.SampleDesc.Count = 1u;
//	descDepth.SampleDesc.Quality = 0u;
//	descDepth.Usage = D3D11_USAGE_DEFAULT;
//	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
//	HR(m_pDevice->CreateTexture2D(&descDepth, nullptr, m_pDepthStencilBuffer.GetAddressOf()));
//
//	//创建深度纹理视图
//	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
//	descDSV.Format = DXGI_FORMAT_D32_FLOAT;
//	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
//	descDSV.Texture2D.MipSlice = 0u;
//	HR(m_pDevice->CreateDepthStencilView(m_pDepthStencilBuffer.Get(), &descDSV, m_pDepthStencilView.GetAddressOf()));

	//绑定深度模板视图
	//m_pContext->OMSetRenderTargets(1u, m_pRenderTarget.GetAddressOf(), m_pDepthStencilView.Get());

	//D3D11_VIEWPORT vp;
	//vp.Width = static_cast<float>(ClientWidth);
	//vp.Height = static_cast<float>(ClientHeight);
	//vp.MinDepth = 0;
	//vp.MaxDepth = 1;
	//vp.TopLeftX = 0;
	//vp.TopLeftY = 0;
	//m_pContext->RSSetViewports(1u, &vp);
	//InitEffect();
	//InitResource();
//}

void Graphics::ClearBuffer(float r, float g, float b)
{
	const float color[4] = { r,g,b,1.0f };
	m_pContext->ClearRenderTargetView(m_pRenderTarget.Get(), color);
	m_pContext->ClearDepthStencilView(m_pDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0u);
}

void Graphics::OnRender(float deltaTime)
{
	ObjectManager::Instance()->DoFrame(deltaTime);
}

void Graphics::OnPresent(UINT SyncInterval, UINT Flags)
{
	HR(m_SwapChain->Present(SyncInterval, Flags));
}


//void Graphics::InitResource()
//{
//	// 设置三角形顶点
//	VertexPosColor vertices[] =
//	{
//		{ XMFLOAT3(0.0f, 0.5f, 0.5f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
//		{ XMFLOAT3(0.5f, -0.5f, 0.5f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
//		{ XMFLOAT3(-0.5f, -0.5f, 0.5f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) }
//	};
//
//	// 设置顶点缓冲区描述
//	D3D11_BUFFER_DESC vbd;
//	ZeroMemory(&vbd, sizeof(vbd));
//	vbd.Usage = D3D11_USAGE_IMMUTABLE;
//	vbd.ByteWidth = sizeof vertices;
//	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
//	vbd.CPUAccessFlags = 0;
//	// 新建顶点缓冲区
//	D3D11_SUBRESOURCE_DATA InitData;
//	ZeroMemory(&InitData, sizeof(InitData));
//	InitData.pSysMem = vertices;
//	HR(m_pDevice->CreateBuffer(&vbd, &InitData, pVertexBuffer.GetAddressOf()));
//
//	// 输入装配阶段的顶点缓冲区设置
//	UINT stride = sizeof(VertexPosColor);	// 跨越字节数
//	UINT offset = 0;						// 起始偏移量
//
//	m_pContext->IASetVertexBuffers(0, 1, pVertexBuffer.GetAddressOf(), &stride, &offset);
//	// 设置图元类型，设定输入布局
//	m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
//	m_pContext->IASetInputLayout(pVertexLayout.Get());
//	// 将着色器绑定到渲染管线
//	m_pContext->VSSetShader(pVertexShader.Get(), nullptr, 0);
//	m_pContext->PSSetShader(pPixelShader.Get(), nullptr, 0);
//}

//void Graphics::InitEffect()
//{
//	ComPtr<ID3DBlob> blob;
//
//	// 创建顶点着色器
//	HR(D3DReadFileToBlob(L"HLSL123\\Triangle_VS.cso", blob.GetAddressOf()));
//	HR(m_pDevice->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, pVertexShader.GetAddressOf()));
//	// 创建并绑定顶点布局
//	HR(m_pDevice->CreateInputLayout(VertexPosColor::inputLayout, ARRAYSIZE(VertexPosColor::inputLayout),
//		blob->GetBufferPointer(), blob->GetBufferSize(), pVertexLayout.GetAddressOf()));
//
//	// 创建像素着色器
//	HR(D3DReadFileToBlob(L"HLSL123\\Triangle_PS.cso",blob.ReleaseAndGetAddressOf()));
//	HR(m_pDevice->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, pPixelShader.GetAddressOf()));
//}
