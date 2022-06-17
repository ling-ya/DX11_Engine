#pragma once
#include<DirectXMath.h>
#include<d3d11.h>


////����һЩ����ṹ�����벼��


/// <summary>
/// ֻ���ж���λ��
/// </summary>
struct VertexPos
{
	VertexPos() = default;
	VertexPos(const VertexPos&) = default;

	VertexPos(VertexPos&&) = default;
	VertexPos& operator=(VertexPos&&) = default;

	constexpr VertexPos(const DirectX::XMFLOAT3 & _pos) : pos(_pos) {}

	DirectX::XMFLOAT3 pos; //����λ��
	static const D3D11_INPUT_ELEMENT_DESC inputLayout[1];//ֻ�ж���λ��
};

/// <summary>
/// ���ж���λ�úͶ�����ɫ
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

	DirectX::XMFLOAT3 pos;//����λ��
	DirectX::XMFLOAT4 color;//������ɫ
	static const D3D11_INPUT_ELEMENT_DESC inputLayout[2];//����λ�ú���ɫ
};


/// <summary>
/// ���ж���λ�� ���� UV
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

	DirectX::XMFLOAT3 pos; //����λ��
	DirectX::XMFLOAT3 normal; //����
	DirectX::XMFLOAT2 tex;   //UV
	static const D3D11_INPUT_ELEMENT_DESC inputLayout[3];
};

/// <summary>
/// ���ж���λ�ã����ߣ� ���ߣ� UV�� COLOR
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

	DirectX::XMFLOAT3 pos;//����λ��
	DirectX::XMFLOAT3 normal; //����
	DirectX::XMFLOAT4 tangent;//����
	DirectX::XMFLOAT2 tex;  //UV
	DirectX::XMFLOAT4 color;  //����ɫ
	static const D3D11_INPUT_ELEMENT_DESC inputLayout[5];
};