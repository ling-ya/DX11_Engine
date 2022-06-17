#pragma once
#include"Component.h"


class Camera :public Component
{
public:
	struct ViewProjBuffer
	{
		DirectX::XMMATRIX view;  //视图矩阵
		DirectX::XMMATRIX proj;  //投影矩阵
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
	ComPtr<ID3D11Buffer> m_pVPConstantBuffer;  //常量缓冲区
	ViewProjBuffer m_bViewProjBuffer;
public:
	//视锥体的属性
	float m_NearZ = 0.0f;
	float m_FarZ = 0.0f;
	float m_Aspect = 0.0f;
	float m_FovY = 0.0f;
};

