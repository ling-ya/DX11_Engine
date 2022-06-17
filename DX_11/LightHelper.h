#pragma once
#include<cstring>
#include<DirectXMath.h>


//方向光(平行光)
struct DirectionalLight
{
	DirectionalLight() = default;
	DirectionalLight(const DirectionalLight&) = default;
	DirectionalLight& operator=(const DirectionalLight&) = default;
	DirectionalLight(DirectionalLight&&) = default;
	DirectionalLight& operator=(DirectionalLight&&) = default;

	DirectionalLight(const DirectX::XMFLOAT4& _ambient, const DirectX::XMFLOAT4& _diffuse, const DirectX::XMFLOAT4& _specular,
		const DirectX::XMFLOAT3& _direction) :
		ambient(_ambient), diffuse(_diffuse), specular(_specular), direction(_direction), pad() {}

	DirectX::XMFLOAT4 ambient; //环境光 
	DirectX::XMFLOAT4 diffuse; //漫反射
	DirectX::XMFLOAT4 specular;//高光
	DirectX::XMFLOAT3 direction;//方向
	float pad; // 最后用一个浮点数填充使得该结构体大小满足16的倍数，便于我们以后在HLSL设置数组
};

//点光源
struct PointLight
{
	PointLight() = default;

	PointLight(const PointLight&) = default;
	PointLight& operator=(const PointLight&) = default;

	PointLight(PointLight&&) = default;
	PointLight& operator=(PointLight&&) = default;


	DirectX::XMFLOAT4 ambient;
	DirectX::XMFLOAT4 diffuse;
	DirectX::XMFLOAT4 specular;

	// 打包成4D向量: (position, range)
	DirectX::XMFLOAT3 position;//位置
	float range;               //范围

	DirectX::XMFLOAT3 att;
	float pad;      //最后用一个浮点数填充使得该结构体大小满足16的倍数，便于我们以后在HLSL设置数组
};

// 聚光灯
struct SpotLight
{
	SpotLight() = default;

	SpotLight(const SpotLight&) = default;
	SpotLight& operator=(const SpotLight&) = default;

	SpotLight(SpotLight&&) = default;
	SpotLight& operator=(SpotLight&&) = default;

	SpotLight(const DirectX::XMFLOAT4& _ambient, const DirectX::XMFLOAT4& _diffuse, const DirectX::XMFLOAT4& _specular,
		const DirectX::XMFLOAT3& _position, float _range, const DirectX::XMFLOAT3& _direction,
		float _spot, const DirectX::XMFLOAT3& _att) :
		ambient(_ambient), diffuse(_diffuse), specular(_specular),
		position(_position), range(_range), direction(_direction), spot(_spot), att(_att), pad() {}

	DirectX::XMFLOAT4 ambient;
	DirectX::XMFLOAT4 diffuse;
	DirectX::XMFLOAT4 specular;

	// 打包成4D向量: (position, range)
	DirectX::XMFLOAT3 position;//位置 
	float range;

	// 打包成4D向量: (direction, spot)
	DirectX::XMFLOAT3 direction;//方向
	float spot; //聚光灯圆锥体区域大小

	// 打包成4D向量: (att, pad)
	DirectX::XMFLOAT3 att;
	float pad; // 最后用一个浮点数填充使得该结构体大小满足16的倍数，便于我们以后在HLSL设置数组
};

// 物体表面材质
//struct Material
//{
//	Material() = default;
//
//	Material(const Material&) = default;
//	Material& operator=(const Material&) = default;
//
//	Material(Material&&) = default;
//	Material& operator=(Material&&) = default;
//
//	Material(const DirectX::XMFLOAT4& _ambient, const DirectX::XMFLOAT4& _diffuse, const DirectX::XMFLOAT4& _specular,
//		const DirectX::XMFLOAT4& _reflect) :
//		ambient(_ambient), diffuse(_diffuse), specular(_specular), reflect(_reflect) {}
//
//	DirectX::XMFLOAT4 ambient;
//	DirectX::XMFLOAT4 diffuse;
//	DirectX::XMFLOAT4 specular; // w = 镜面反射强度
//	DirectX::XMFLOAT4 reflect;
//};

