#pragma once

#include "DXTrace.h"
#include"Graphics.h"
#include"StringConvert.h"

class Shader
{
public:
	Shader();
	~Shader() = default;
	static Shader* Find(string filename);
	ID3DBlob* GetByteCode() const noexcept;

public:
	ComPtr<ID3DBlob> m_pBytecodeBlob;
	ComPtr<ID3D11VertexShader> m_pVertexShader;
	ComPtr<ID3D11PixelShader> m_pPixelShader;

	//ComPtr<ID3DX11Effect> m_pEffect;                     //effect÷∏’Î
};

