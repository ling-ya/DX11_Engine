#pragma once
#include<wrl/client.h>
//#include <d3dcommon.h>
//#include <dxgi.h>
#include <d3d11_1.h>
//#include <d3d11_2.h>
#include <d3dcompiler.h>
#include<DirectXMath.h>
#include"DXTrace.h"
//#include <d3dx11effect.h>


#pragma comment(lib, "d3d11.lib")
//#pragma comment(lib, "dxgi.lib")
//#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "winmm.lib")
//#pragma comment(lib, "comctl32.lib")
//#pragma comment(lib, "usp10.lib")
//#pragma warning( disable : 4481 )
using namespace Microsoft::WRL;
using namespace DirectX;
class Graphics
{
public:
	struct VertexPosColor
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT4 color;
		static const D3D11_INPUT_ELEMENT_DESC inputLayout[2];
	};

public:
	Graphics(HWND hwnd,UINT wilth,UINT height);
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	~Graphics() = default;
	//void Init(int ClientWidth,int ClientHeight);
	void ClearBuffer(float r, float g, float b);
	void OnRender(float deltaTime);
	//void InitResource();
	//void InitEffect();
public:
	HWND m_Hwnd;
	static ComPtr<ID3D11Device> m_pDevice;
	static ComPtr<ID3D11DeviceContext> m_pContext;
	ComPtr<IDXGISwapChain> m_SwapChain;
	ComPtr<ID3D11RenderTargetView> m_pRenderTarget;
	ComPtr<ID3D11DepthStencilView> m_pDepthStencilView;   //深度模板视图
	ComPtr<ID3D11Texture2D> m_pDepthStencilBuffer;        // 深度模板缓冲区
	D3D11_VIEWPORT m_ScreenViewport;                      //视口

	//ComPtr<ID3D11InputLayout> pVertexLayout;	// 顶点输入布局
	//ComPtr<ID3D11Buffer> pVertexBuffer;		// 顶点缓冲区
	//ComPtr<ID3D11VertexShader> pVertexShader;	// 顶点着色器
	//ComPtr<ID3D11PixelShader> pPixelShader;	// 像素着色器

};

