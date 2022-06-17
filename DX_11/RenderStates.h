//�ṩһЩ��Ⱦ״̬

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
	static ComPtr<ID3D11RasterizerState> RSWireframe;    // ��դ����״̬���߿�ģʽ
	static ComPtr<ID3D11RasterizerState> RSNoCull;       // ��դ����״̬���ޱ���ü�ģʽ

	static ComPtr<ID3D11BlendState> BSNoColorWrite;      //���״̬����д����ɫ
	static ComPtr<ID3D11BlendState> BSTransparent;       // ���״̬��͸�����
	static ComPtr<ID3D11BlendState> BSAlphaToCoverage;	// ���״̬��Alpha-To-Coverage

	static ComPtr<ID3D11DepthStencilState> DSSWriteStencil; //���/ģ��״̬��д��ģ��ֵ
	static ComPtr<ID3D11DepthStencilState> DSSDrawWithStencil;	// ���/ģ��״̬����ָ��ģ��ֵ��������л���
	static ComPtr<ID3D11DepthStencilState> DSSNoDoubleBlend;    //���/ģ��״̬���޶��λ������
	static ComPtr<ID3D11DepthStencilState> DSSNoDepthTest;      //���/ģ��״̬���ر���Ȳ���
	static ComPtr<ID3D11DepthStencilState> DSSNoDepthWrite;     //���/ģ��״̬������Ȳ��ԣ���д�����ֵ
};

