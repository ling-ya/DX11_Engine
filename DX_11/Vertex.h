#pragma once
#include<DirectXMath.h>
#include<d3d11.h>


////定义一些顶点结构和输入布局


/// <summary>
/// 只具有顶点位置
/// </summary>
struct VertexPos
{
	VertexPos() = default;
	VertexPos(const VertexPos&) = default;

	VertexPos(VertexPos&&) = default;
	VertexPos& operator=(VertexPos&&) = default;

	constexpr VertexPos(const DirectX::XMFLOAT3 & _pos) : pos(_pos) {}

	DirectX::XMFLOAT3 pos; //顶点位置
	static const D3D11_INPUT_ELEMENT_DESC inputLayout[1];//只有顶点位置
};

/// <summary>
/// 具有顶点位置和顶点颜色
/// </summary>
struct VertexPosColor
{
	VertexPosColor() = default;

	VertexPosColor(const VertexPosColor&) = default;
	VertexPosColor& operator=(const VertexPosColor&) = default;

	VertexPosColor(VertexPosColor&&) = default;
	VertexPosColor& operator=(VertexPosColor&&) = default;

	constexpr VertexPosColor(const DirectX::XMFLOAT3& _pos, const DirectX::XMFLOAT4& _color) :
		pos(_pos), color(_color) {}

	DirectX::XMFLOAT3 pos;//顶点位置
	DirectX::XMFLOAT4 color;//顶点颜色
	static const D3D11_INPUT_ELEMENT_DESC inputLayout[2];//顶点位置和颜色
};


/// <summary>
/// 具有顶点位置 法线 UV
/// </summary>
struct VertexPosNormalTex
{
	VertexPosNormalTex() = default;

	VertexPosNormalTex(const VertexPosNormalTex&) = default;
	VertexPosNormalTex& operator=(const VertexPosNormalTex&) = default;

	VertexPosNormalTex(VertexPosNormalTex&&) = default;
	VertexPosNormalTex& operator=(VertexPosNormalTex&&) = default;

	constexpr VertexPosNormalTex(const DirectX::XMFLOAT3& _pos, const DirectX::XMFLOAT3& _normal,
		const DirectX::XMFLOAT2& _tex) :
		pos(_pos), normal(_normal), tex(_tex) {}

	DirectX::XMFLOAT3 pos; //顶点位置
	DirectX::XMFLOAT3 normal; //法线
	DirectX::XMFLOAT2 tex;   //UV
	static const D3D11_INPUT_ELEMENT_DESC inputLayout[3];
};

/// <summary>
/// 具有顶点位置，法线， 切线， UV， COLOR
/// </summary>
struct VertexPosNormalTangentTexColor
{
	VertexPosNormalTangentTexColor() = default;

	VertexPosNormalTangentTexColor(const VertexPosNormalTangentTexColor&) = default;
	VertexPosNormalTangentTexColor& operator=(const VertexPosNormalTangentTexColor&) = default;

	VertexPosNormalTangentTexColor(VertexPosNormalTangentTexColor&&) = default;
	VertexPosNormalTangentTexColor& operator=(VertexPosNormalTangentTexColor&&) = default;

	constexpr VertexPosNormalTangentTexColor(const DirectX::XMFLOAT3& _pos, const DirectX::XMFLOAT3& _normal,
		const DirectX::XMFLOAT4& _tangent, const DirectX::XMFLOAT2& _tex, const DirectX::XMFLOAT4& _color) :
		pos(_pos), normal(_normal), tangent(_tangent), tex(_tex), color(_color){}

	DirectX::XMFLOAT3 pos;//顶点位置
	DirectX::XMFLOAT3 normal; //法线
	DirectX::XMFLOAT4 tangent;//切线
	DirectX::XMFLOAT2 tex;  //UV
	DirectX::XMFLOAT4 color;  //顶点色
	static const D3D11_INPUT_ELEMENT_DESC inputLayout[5];
};