#pragma once
#include"Component.h"
#include"Graphics.h"
#include"LightHelper.h"
class Light  : public Component
{
public:
	struct CBLight 
	{
		DirectionalLight dirLight[10];
		PointLight pointLight[10];
		SpotLight spotLight[10];
		XMFLOAT4 sysPos;
		int numDirLight;
		int numPointLight;
		int numSpotLight;
		float pad;		// 打包保证16字节对齐
	};



public:
	Light();
	~Light() = default;
	virtual void Start();
	virtual void Update(float deltaTime);

public:
	ComPtr<ID3D11Buffer> m_pConstantBuffer; //常量缓冲区
	CBLight m_CBLight;                      //存放灯光的缓冲区

};

