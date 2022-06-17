#include "VertexShader.h"
VertexShader::VertexShader()
{

}

void VertexShader::Find(const WCHAR* csoFileNameInOut)
{
	//VertexShader* pVertexShader = new VertexShader();
	HR(D3DReadFileToBlob(csoFileNameInOut, m_pBytecodeBlob.GetAddressOf()));
	HR(Graphics::m_pDevice->CreateVertexShader(m_pBytecodeBlob->GetBufferPointer(), m_pBytecodeBlob->GetBufferSize(), nullptr, m_pVertexShader.GetAddressOf()));
}

ID3DBlob* VertexShader::GetBytecode() const noexcept
{
	return m_pBytecodeBlob.Get();
}
