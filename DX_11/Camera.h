#pragma once
#include"Component.h"


class Camera :public Component
{
public:
	struct ViewProjBuffer
	{
		DirectX::XMMATRIX view;  //��ͼ����
		DirectX::XMMATRIX proj;  //ͶӰ����
	};

public:
	Camera();
	~Camera() = default;
	virtual void Start();
	virtual void Update(float deltaTime);

	XMMATRIX GetViewXM()const;
	XMMATRIX GetProjXM()const;
	XMMATRIX GetViewProjXM()const;

	void SetFrustum(float fovY, float aspect, float nearZ, float farZ);
public:
	ComPtr<ID3D11Buffer> m_pVPConstantBuffer;  //����������
	ViewProjBuffer m_bViewProjBuffer;
public:
	//��׶�������
	float m_NearZ = 0.0f;
	float m_FarZ = 0.0f;
	float m_Aspect = 0.0f;
	float m_FovY = 0.0f;
};

