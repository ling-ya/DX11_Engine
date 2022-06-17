#pragma once
#include"DXTrace.h"
#include"Graphics.h"

class VertexShader
{
public:
	VertexShader();
	~VertexShader() = default;
	void Find(const WCHAR * csoFileNameInOut);
	ID3DBlob* GetBytecode() const noexcept;
public:
	ComPtr<ID3DBlob> m_pBytecodeBlob;
	ComPtr<ID3D11VertexShader> m_pVertexShader;
};

