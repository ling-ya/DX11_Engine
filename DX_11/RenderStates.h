//提供一些渲染状态

#pragma once
#include<wrl/client.h>
#include<d3d11_1.h>

using namespace Microsoft::WRL;
class RenderStates
{
public:
	static bool ISInit();
	static void InitAll(ID3D11Device* pdevice);

public:
	static ComPtr<ID3D11RasterizerState> RSWireframe;    // 光栅化器状态：线框模式
	static ComPtr<ID3D11RasterizerState> RSNoCull;       // 光栅化器状态：无背面裁剪模式

	static ComPtr<ID3D11BlendState> BSNoColorWrite;      //混合状态：不写入颜色
	static ComPtr<ID3D11BlendState> BSTransparent;       // 混合状态：透明混合
	static ComPtr<ID3D11BlendState> BSAlphaToCoverage;	// 混合状态：Alpha-To-Coverage
};

