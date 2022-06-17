#include "Transform.h"

Transform::Transform() 
{
}

Transform::Transform(const XMFLOAT3& scale, const XMFLOAT3& rotation, const XMFLOAT3& position) :
	m_Scale(scale),
	m_Rotation(rotation),
	m_Position(position)
{

}

void Transform::Start()
{
}

void Transform::Update(float deltaTime)
{
}

XMFLOAT3 Transform::GetSacle()const 
{
	return m_Scale;
}

XMVECTOR Transform::GetScaleXM() const
{
	return XMLoadFloat3(&m_Scale);
}

XMFLOAT3 Transform::GetRotation() const
{
	return m_Rotation;
}

XMVECTOR Transform::GetRotationXM() const
{
	return XMLoadFloat3(&m_Rotation);
}

XMFLOAT3 Transform::GetPosition() const
{
	return m_Position;
}

XMVECTOR Transform::GetPositionXM() const
{
	return XMLoadFloat3(&m_Position);
}

XMFLOAT3 Transform::GetRightAxis()const
{
	XMMATRIX R = XMMatrixRotationRollPitchYawFromVector(XMLoadFloat3(&m_Rotation));
	XMFLOAT3 right;
	XMStoreFloat3(&right, R.r[0]);
	return right;
}

XMVECTOR Transform::GetRightAxisXM()const
{
	XMFLOAT3 right = GetRightAxis();
	return XMLoadFloat3(&right);
}

XMFLOAT3 Transform::GetUpAxis()const
{
	XMMATRIX R = XMMatrixRotationRollPitchYawFromVector(XMLoadFloat3(&m_Rotation));
	XMFLOAT3 up;
	XMStoreFloat3(&up, R.r[1]);
	return up;
}
XMVECTOR Transform::GetUpAxisXM()const
{
	XMFLOAT3 up = GetUpAxis();
	return XMLoadFloat3(&up);
}

XMFLOAT3 Transform::GetForwardAxis()const
{
	XMMATRIX R = XMMatrixRotationRollPitchYawFromVector(XMLoadFloat3(&m_Rotation));
	XMFLOAT3 forward;
	XMStoreFloat3(&forward, R.r[2]);
	return forward;
}

XMVECTOR Transform::GetForwardAxisXM()const
{
	XMFLOAT3 forward = GetForwardAxis();
	return XMLoadFloat3(&forward);
}

XMFLOAT4X4 Transform::GetLocalToWorldMatrix()const
{
	XMFLOAT4X4 res;
	XMStoreFloat4x4(&res, GetLocalToWorldMatrixXM());
	return res;
}

XMMATRIX Transform::GetLocalToWorldMatrixXM()const
{
	XMVECTOR scaleVec = XMLoadFloat3(&m_Scale);
	XMVECTOR rotationVec = XMLoadFloat3(&m_Rotation);
	XMVECTOR positionVec = XMLoadFloat3(&m_Position);
	XMMATRIX localToWorld = XMMatrixScalingFromVector(scaleVec) * XMMatrixRotationRollPitchYawFromVector(rotationVec) * XMMatrixTranslationFromVector(positionVec);
	return localToWorld;
}

XMFLOAT4X4 Transform::GetWorldToLocalMatrix()const
{
	XMFLOAT4X4 res;
	XMStoreFloat4x4(&res, GetWorldToLocalMatrixXM());
	return res;
}

/// <summary>
/// 为世界矩阵的逆矩阵
/// </summary>
/// <returns></returns>
XMMATRIX Transform::GetWorldToLocalMatrixXM()const
{
	XMMATRIX worldToLocal = XMMatrixInverse(nullptr, GetLocalToWorldMatrixXM());
	return worldToLocal;
}

void Transform::SetScale(const XMFLOAT3& scale)
{
	m_Scale = scale;
}

void Transform::SetScale(float x, float y, float z)
{
	m_Scale = XMFLOAT3(x, y, z);
}

void Transform::SetRotation(const XMFLOAT3& eulerAnglesInRadian)
{
	m_Rotation = eulerAnglesInRadian;
}

void Transform::SetRotation(float x, float y, float z)
{
	m_Rotation = XMFLOAT3(x, y, z);
}

void Transform::SetPosition(const XMFLOAT3& position)
{
	m_Position = position;
}

void Transform::SetPosition(float x, float y, float z)
{
	m_Position = XMFLOAT3(x, y, z);
}

void Transform::Rotate(const XMFLOAT3& eulerAnglesInRadian)
{
	XMVECTOR newRotationVec = XMVectorAdd(XMLoadFloat3(&m_Rotation), XMLoadFloat3(&eulerAnglesInRadian));
	XMStoreFloat3(&m_Rotation, newRotationVec);
}


void Transform::RotateAxis(const XMFLOAT3& axis, float radian)
{
	XMVECTOR rotation = XMLoadFloat3(&m_Rotation);
	XMMATRIX R = XMMatrixRotationRollPitchYawFromVector(rotation) * XMMatrixRotationAxis(XMLoadFloat3(&axis), radian);
	XMFLOAT4X4 roMatrix;
	XMStoreFloat4x4(&roMatrix, R);
	m_Rotation = GetEulerAnglesFromRotationMatrix(roMatrix);
}

void Transform::RotateAround(const XMFLOAT3& point, const XMFLOAT3& axis, float radian)
{
	XMVECTOR rotationVec = XMLoadFloat3(&m_Rotation);
	XMVECTOR positionVec = XMLoadFloat3(&m_Position);
	XMVECTOR centerVec = XMLoadFloat3(&point);

	//以point作为原点进行旋转
	XMMATRIX RT = XMMatrixRotationRollPitchYawFromVector(rotationVec) * XMMatrixTranslationFromVector(positionVec - centerVec);
	RT *= XMMatrixRotationAxis(XMLoadFloat3(&axis), radian);
	RT *= XMMatrixTranslationFromVector(centerVec);
	XMFLOAT4X4 rotMattrix;
	XMStoreFloat4x4(&rotMattrix, RT);
	m_Rotation = GetEulerAnglesFromRotationMatrix(rotMattrix);
	XMStoreFloat3(&m_Position, RT.r[3]);
}

void Transform::Translate(const XMFLOAT3& direction, float magnitude) 
{
	XMVECTOR directionVec = XMVector3Normalize(XMLoadFloat3(&direction));
	XMVECTOR newPosition = XMVectorMultiplyAdd(XMVectorReplicate(magnitude), directionVec, XMLoadFloat3(&m_Position));
	XMStoreFloat3(&m_Position, newPosition);
}

void Transform::LookAt(const XMFLOAT3& target, const XMFLOAT3& up)
{
	XMMATRIX View = XMMatrixLookAtLH(XMLoadFloat3(&m_Position), XMLoadFloat3(&target), XMLoadFloat3(&up));
	XMMATRIX InvView = XMMatrixInverse(nullptr, View);
	XMFLOAT4X4 rotMatrix;
	XMStoreFloat4x4(&rotMatrix, InvView);
	m_Rotation = GetEulerAnglesFromRotationMatrix(rotMatrix);
}

void Transform::LookTo(const XMFLOAT3& directtion, const XMFLOAT3& up)
{
	XMMATRIX View = XMMatrixLookAtLH(XMLoadFloat3(&m_Position), XMLoadFloat3(&directtion), XMLoadFloat3(&up));
	XMMATRIX InvView = XMMatrixInverse(nullptr, View);
	XMFLOAT4X4 rotMatrix;
	XMStoreFloat4x4(&rotMatrix, InvView);
	m_Rotation = GetEulerAnglesFromRotationMatrix(rotMatrix);
}

XMFLOAT3 Transform::GetEulerAnglesFromRotationMatrix(const XMFLOAT4X4& rotationMatrix)
{
	//通过旋转矩阵反求欧拉角
	float c = sqrtf(1.0f - rotationMatrix(2, 1) * rotationMatrix(2, 1));

	if (isnan(c))
	{
		c = 0.0f;
	}
	XMFLOAT3 rotation = {};
	rotation.z = atan2f(rotationMatrix(0, 1), rotationMatrix(1, 1));
	rotation.x = atan2f(-rotationMatrix(2, 1), c);
	rotation.y = atan2f(rotationMatrix(2, 1), rotationMatrix(2, 2));
	return rotation;
}

