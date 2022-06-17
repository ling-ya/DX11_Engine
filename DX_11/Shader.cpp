#include "Shader.h"

Shader::Shader()
{
}

Shader* Shader::Find(string filename)
{
	Shader* pShader = new Shader();

	//创建顶点着色器
	wstring VS_ShaderName = L"_VS.cso";
	VS_ShaderName = StringConvert::StringToWString(filename) + VS_ShaderName;
	HR(D3DReadFileToBlob(VS_ShaderName.c_str(), pShader->m_pBytecodeBlob.GetAddressOf()));
	HR(Graphics::m_pDevice->CreateVertexShader(pShader->m_pBytecodeBlob->GetBufferPointer(), pShader->m_pBytecodeBlob->GetBufferSize(), nullptr, pShader->m_pVertexShader.GetAddressOf()));



	//创建像素着色器
	wstring PS_ShaderName = L"_PS.cso";
	PS_ShaderName = StringConvert::StringToWString(filename) + PS_ShaderName;
	ComPtr<ID3DBlob> m_pixelBlob;
	HR(D3DReadFileToBlob(PS_ShaderName.c_str(), m_pixelBlob.GetAddressOf()));
	HR(Graphics::m_pDevice->CreatePixelShader(m_pixelBlob->GetBufferPointer(), m_pixelBlob->GetBufferSize(), nullptr, pShader->m_pPixelShader.GetAddressOf()));



//	//使用FX11框架
//
//	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
//#ifdef _DEBUG
//	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
//	// Setting this flag improves the shader debugging experience, but still allows 
//	// the shaders to be optimized and to run exactly the way they will run in 
//	// the release configuration of this program.
//	dwShaderFlags |= D3DCOMPILE_DEBUG;
//
//	// Disable optimizations to further improve shader debugging
//	dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
//#endif
//
//
//#if D3D_COMPILER_VERSION>=46
//	wstring filepath = StringConvert::StringToWString(filename);
//	ComPtr<ID3DBlob> pErrorBlob=nullptr;
//	HR(D3DX11CompileEffectFromFile(filepath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, dwShaderFlags, 0, Graphics::m_pDevice.Get(), pShader->m_pEffect.GetAddressOf(), pErrorBlob.GetAddressOf()));
//	if (pErrorBlob !=nullptr)
//	{
//		OutputDebugStringA(reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer()));
//	}
//#endif

	return pShader;
}

ID3DBlob* Shader::GetByteCode() const noexcept
{
	return m_pBytecodeBlob.Get();
}
