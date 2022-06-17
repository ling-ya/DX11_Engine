#include "PixelShader.h"

PixelShader::PixelShader()
{
}

void PixelShader::Find(const WCHAR* csoFileNameInOut)
{
	ComPtr<ID3DBlob> m_pBytecodeBlob;
	HR(D3DReadFileToBlob(csoFileNameInOut, m_pBytecodeBlob.GetAddressOf()));
	HR(Graphics::m_pDevice->CreatePixelShader(m_pBytecodeBlob->GetBufferPointer(), m_pBytecodeBlob->GetBufferSize(), nullptr, m_pPixelShader.GetAddressOf()));
}
