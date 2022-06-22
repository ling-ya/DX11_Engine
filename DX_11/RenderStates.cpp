#include "RenderStates.h"
#include "DXTrace.h"

ComPtr<ID3D11RasterizerState> RenderStates::RSNoCull = nullptr;
ComPtr<ID3D11RasterizerState> RenderStates::RSWireframe = nullptr;
ComPtr<ID3D11RasterizerState> RenderStates::RSCullClockWise = nullptr;

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
    rasterizerDesc.FrontCounterClockwise = false;
    rasterizerDesc.DepthClipEnable = true;
    HR(pdevice->CreateRasterizerState(&rasterizerDesc, RSNoCull.GetAddressOf()));

    // ˳ʱ���޳�ģʽ
    rasterizerDesc.FillMode = D3D11_FILL_SOLID;
    rasterizerDesc.CullMode = D3D11_CULL_BACK;
    rasterizerDesc.FrontCounterClockwise = true;
    rasterizerDesc.DepthClipEnable = true;
    HR(pdevice->CreateRasterizerState(&rasterizerDesc, RSCullClockWise.GetAddressOf()));

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
    rtDesc.BlendEnable = true;
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
    rtDesc.BlendEnable = false;
    rtDesc.SrcBlend = D3D11_BLEND_ZERO;
    rtDesc.DestBlend = D3D11_BLEND_ONE;
    rtDesc.BlendOp = D3D11_BLEND_OP_ADD;
    rtDesc.SrcBlendAlpha = D3D11_BLEND_ZERO;
    rtDesc.DestBlendAlpha = D3D11_BLEND_ONE;
    rtDesc.BlendOpAlpha = D3D11_BLEND_OP_ADD;
    rtDesc.RenderTargetWriteMask = 0;
    HR(pdevice->CreateBlendState(&blendDesc, BSNoColorWrite.GetAddressOf()));

    //******************************
    //��ʼ�����/ģ��״̬

    D3D11_DEPTH_STENCIL_DESC dsDesc;

    //���������/ģ��״̬
    //���ﲻд�������Ϣ
    //���������滹�Ǳ��棬ԭ��ָ��������Ķ��ᱻд��StencilRef
    dsDesc.DepthEnable = true;
    dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
    dsDesc.DepthFunc = D3D11_COMPARISON_LESS;

    dsDesc.StencilEnable = true;
    dsDesc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
    dsDesc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;

    dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
    dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_REPLACE;
    dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
    // ���ڱ���ļ����������ǲ�������Ⱦ�ģ���������������޹ؽ�Ҫ
    dsDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    dsDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
    dsDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_REPLACE;
    dsDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

    HR(pdevice->CreateDepthStencilState(&dsDesc, DSSWriteStencil.GetAddressOf()));


    //����������/ģ��״̬
    //����Ҫ���Ʒ��侵�棬��Ҫ�������
    //����������ģ��ֵ�͵�ǰ����ģ��ֵ���ʱ�Ż���л���
    dsDesc.DepthEnable = true;
    dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    dsDesc.DepthFunc = D3D11_COMPARISON_LESS;

    dsDesc.StencilEnable = true;
    dsDesc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
    dsDesc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;

    dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
    dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_EQUAL;
    // ���ڱ���ļ����������ǲ�������Ⱦ�ģ���������������޹ؽ�Ҫ
    dsDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    dsDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
    dsDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    dsDesc.BackFace.StencilFunc = D3D11_COMPARISON_EQUAL;

    HR(pdevice->CreateDepthStencilState(&dsDesc, DSSDrawWithStencil.GetAddressOf()));

    // �޶��λ�����/ģ��״̬
    // ����Ĭ����Ȳ���
    // ͨ���Ե���ʹ��ԭ��StencilRef��ֵֻ��ʹ��һ�Σ�ʵ�ֽ�һ�λ��
    dsDesc.DepthEnable = true;
    dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    dsDesc.DepthFunc = D3D11_COMPARISON_LESS;

    dsDesc.StencilEnable = true;
    dsDesc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
    dsDesc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;

    dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
    dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_INCR;
    dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_EQUAL;
    // ���ڱ���ļ����������ǲ�������Ⱦ�ģ���������������޹ؽ�Ҫ
    dsDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    dsDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
    dsDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_INCR;
    dsDesc.BackFace.StencilFunc = D3D11_COMPARISON_EQUAL;

    HR(pdevice->CreateDepthStencilState(&dsDesc, DSSNoDoubleBlend.GetAddressOf()));

    // �ر���Ȳ��Ե����/ģ��״̬���ر���Ȳ��Ժ󣬾�û�����д��
    // �����Ʒ�͸�����壬����ϸ��ջ���˳��
    // ����͸����������Ҫ���Ļ���˳��
    // ��Ĭ�������ģ����Ծ��ǹرյ�
    dsDesc.DepthEnable = false;
    dsDesc.StencilEnable = false;
    HR(pdevice->CreateDepthStencilState(&dsDesc, DSSNoDepthTest.GetAddressOf()));

    //������Ȳ��ԣ�����д�����ֵ��״̬
    //�����Ʒ�͸�������壬Ӧʹ��Ĭ��״̬
    //����͸������ʱ��ʹ�ø�״̬������Чȷ�����״̬�Ľ���
    //����ȷ����ǰ�ķ�͸����������赲�Ϻ��һ������
    dsDesc.DepthEnable = true;
    dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
    dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
    dsDesc.StencilEnable = false;
    HR(pdevice->CreateDepthStencilState(&dsDesc, DSSNoDepthWrite.GetAddressOf()));
}
