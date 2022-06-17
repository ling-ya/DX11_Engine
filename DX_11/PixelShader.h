#pragma once
#include"DXTrace.h"
#include"Graphics.h"

class PixelShader
{
public:
	PixelShader();
	~PixelShader() = default;

	void Find(const WCHAR* csoFileNameInOut);

public:
	ComPtr<ID3D11PixelShader> m_pPixelShader;
};

