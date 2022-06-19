#include "RenderStates.h"
#include "DXTrace.h"

ComPtr<ID3D11RasterizerState> RenderStates::RSNoCull = nullptr;
ComPtr<ID3D11RasterizerState> RenderStates::RSWireframe = nullptr;

ComPtr<ID3D11BlendState> RenderStates::BSAlphaToCoverage = nullptr;
ComPtr<ID3D11BlendState> RenderStates::BSNoColorWrite = nullptr;
ComPtr<ID3D11BlendState> RenderStates::BSTransparent = nullptr;

ComPtr<ID3D11DepthStencilState> RenderStates::DSSWriteStencil = nullptr;
ComPtr<ID3D11DepthStencilState> RenderStates::DSSDrawWithStencil = nullptr;
ComPtr<ID3D11DepthStencilState> RenderStates::DSSNoDoubleBlend = nullptr;
ComPtr<ID3D11DepthStencilState> RenderStates::DSSNoDepthTest = nullptr;
ComPtr<ID3D11DepthStencilState> RenderStates::DSSNoDepthWrite = nullptr;



bool RenderStates::ISInit()
{
    return RSWireframe != nullptr;
}

void RenderStates::InitAll(ID3D11Device* pdevice)
{
    if (ISInit())
        return;

    //��ʼ����դ����״̬
    D3D11_RASTERIZER_DESC rasterizerDesc;
    ZeroMemory(&rasterizerDesc, sizeof(rasterizerDesc));

    //�߿�ģʽ
    rasterizerDesc.FillMode = D3D11_FILL_WIREFRAME;
    rasterizerDesc.CullMode = D3D11_CULL_NONE;
    rasterizerDesc.FrontCounterClockwise = false;
    rasterizerDesc.DepthClipEnable = true;
    HR(pdevice->CreateRasterizerState(&rasterizerDesc, RSWireframe.GetAddressOf()));

    //�ޱ����޳�ģʽ
    rasterizerDesc.FillMode = D3D11_FILL_SOLID;
    rasterizerDesc.CullMode = D3D11_CULL_NONE;
    rasterizerDesc.AntialiasedLineEnable = false;
    rasterizerDesc.DepthClipEnable = true;
    HR(pdevice->CreateRasterizerState(&rasterizerDesc, RSNoCull.GetAddressOf()));

    //��ʼ�����״̬
    D3D11_BLEND_DESC blendDesc;
    ZeroMemory(&blendDesc, sizeof(blendDesc));
    auto& rtDesc = blendDesc.RenderTarget[0];

    //Alpha-To-Coverageģʽ
    blendDesc.AlphaToCoverageEnable = true;
    blendDesc.IndependentBlendEnable = false;
    rtDesc.BlendEnable = false;
    rtDesc.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    HR(pdevice->CreateBlendState(&blendDesc, BSAlphaToCoverage.GetAddressOf()));

    //͸�����ģʽ
    //Color = SrcAlpha * SrcColor + (1 - SrcAlpha) * DestColor 
    //Alpha = SrcAlpha;
    blendDesc.AlphaToCoverageEnable = false;
    blendDesc.IndependentBlendEnable = false;
    rtDesc.BlendEnable = true;//�������
    rtDesc.SrcBlend = D3D11_BLEND_SRC_ALPHA;
    rtDesc.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
    rtDesc.BlendOp = D3D11_BLEND_OP_ADD;
    rtDesc.SrcBlendAlpha = D3D11_BLEND_ONE;
    rtDesc.DestBlendAlpha = D3D11_BLEND_ZERO;
    rtDesc.BlendOpAlpha = D3D11_BLEND_OP_ADD;
    HR(pdevice->CreateBlendState(&blendDesc, BSTransparent.GetAddressOf()));

    //����ɫд��ģʽ
    // Color = DestColor
    // Alpha = DestAlpha
    rtDesc.SrcBlend = D3D11_BLEND_ZERO;
    rtDesc.DestBlend = D3D11_BLEND_ONE;
    rtDesc.BlendOp = D3D11_BLEND_OP_ADD;
    rtDesc.SrcBlendAlpha = D3D11_BLEND_ZERO;
    rtDesc.DestBlendAlpha = D3D11_BLEND_ONE;
    rtDesc.BlendOpAlpha = D3D11_BLEND_OP_ADD;
    HR(pdevice->CreateBlendState(&blendDesc, BSNoColorWrite.GetAddressOf()));
}
