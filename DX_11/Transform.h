#pragma once
#include"Component.h"
class Transform :public Component
{
public:
	Transform();
	Transform(const XMFLOAT3& scale, const XMFLOAT3& rotation, const XMFLOAT3& position);
	~Transform() = default;
	virtual void Start();
	virtual void Update(float deltaTime);

	//获得对象的缩放比
	XMFLOAT3 GetSacle()const;
	XMVECTOR GetScaleXM()const;

	//获取对象欧拉角
	XMFLOAT3 GetRotation()const;
	XMVECTOR GetRotationXM() const;

	//获得对象的位置
	XMFLOAT3 GetPosition()const;
	XMVECTOR GetPositionXM()const;

	//获得右方向轴
	XMFLOAT3 GetRightAxis()const;
	XMVECTOR GetRightAxisXM()const;

	//获得上方向轴
	XMFLOAT3 GetUpAxis()const;
	XMVECTOR GetUpAxisXM()const;

	//获得前方向轴
	XMFLOAT3 GetForwardAxis()const;
	XMVECTOR GetForwardAxisXM()const;

	//获得局部-世界变换矩阵
	XMFLOAT4X4 GetLocalToWorldMatrix()const;
	XMMATRIX GetLocalToWorldMatrixXM()const;

	//获取世界-局部变换矩阵
	XMFLOAT4X4 GetWorldToLocalMatrix()const;
	XMMATRIX GetWorldToLocalMatrixXM()const;

	//设置对象缩放比例
	void SetScale(const XMFLOAT3& scale);
	void SetScale(float x, float y, float z);

	// 设置对象欧拉角(弧度制)
	// 对象将以Z-X-Y轴顺序旋转
	void SetRotation(const XMFLOAT3& eulerAnglesInRadian);
	void SetRotation(float x, float y, float z);

	//设置对象位置
	void SetPosition(const XMFLOAT3& position);
	void SetPosition(float x, float y, float z);

	//指定欧拉角旋转对象
	void Rotate(const XMFLOAT3& eulerAnglesInRadian);

	//指定以原点为中心绕轴旋转
	void RotateAxis(const XMFLOAT3 & axis, float radian);

	//指定以point为旋转中心绕轴旋转
	void RotateAround(const XMFLOAT3& point, const XMFLOAT3& axis, float radian);

	//沿着某一方向平移
	void Translate(const XMFLOAT3& direction, float magnitude);

	//观察某一点
	void LookAt(const XMFLOAT3& target, const XMFLOAT3& up = { 0.0f,1.0f,0.0f });

	//沿着某一方向观察
	void LookTo(const XMFLOAT3& direction, const XMFLOAT3& up = { 0.0f,1.0f,0.0f });

public:
	//从旋转矩阵中获取欧拉角
	XMFLOAT3 GetEulerAnglesFromRotationMatrix(const XMFLOAT4X4& rotationMatrix);

public:
	XMFLOAT3 m_Scale = { 1.0f,1.0f,1.0f };    //缩放
	XMFLOAT3 m_Rotation = {};                  //旋转欧拉角(弧度制)
	XMFLOAT3 m_Position = {};                  //位置
};

