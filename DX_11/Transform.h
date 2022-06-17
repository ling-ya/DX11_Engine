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

	//��ö�������ű�
	XMFLOAT3 GetSacle()const;
	XMVECTOR GetScaleXM()const;

	//��ȡ����ŷ����
	XMFLOAT3 GetRotation()const;
	XMVECTOR GetRotationXM() const;

	//��ö����λ��
	XMFLOAT3 GetPosition()const;
	XMVECTOR GetPositionXM()const;

	//����ҷ�����
	XMFLOAT3 GetRightAxis()const;
	XMVECTOR GetRightAxisXM()const;

	//����Ϸ�����
	XMFLOAT3 GetUpAxis()const;
	XMVECTOR GetUpAxisXM()const;

	//���ǰ������
	XMFLOAT3 GetForwardAxis()const;
	XMVECTOR GetForwardAxisXM()const;

	//��þֲ�-����任����
	XMFLOAT4X4 GetLocalToWorldMatrix()const;
	XMMATRIX GetLocalToWorldMatrixXM()const;

	//��ȡ����-�ֲ��任����
	XMFLOAT4X4 GetWorldToLocalMatrix()const;
	XMMATRIX GetWorldToLocalMatrixXM()const;

	//���ö������ű���
	void SetScale(const XMFLOAT3& scale);
	void SetScale(float x, float y, float z);

	// ���ö���ŷ����(������)
	// ������Z-X-Y��˳����ת
	void SetRotation(const XMFLOAT3& eulerAnglesInRadian);
	void SetRotation(float x, float y, float z);

	//���ö���λ��
	void SetPosition(const XMFLOAT3& position);
	void SetPosition(float x, float y, float z);

	//ָ��ŷ������ת����
	void Rotate(const XMFLOAT3& eulerAnglesInRadian);

	//ָ����ԭ��Ϊ����������ת
	void RotateAxis(const XMFLOAT3 & axis, float radian);

	//ָ����pointΪ��ת����������ת
	void RotateAround(const XMFLOAT3& point, const XMFLOAT3& axis, float radian);

	//����ĳһ����ƽ��
	void Translate(const XMFLOAT3& direction, float magnitude);

	//�۲�ĳһ��
	void LookAt(const XMFLOAT3& target, const XMFLOAT3& up = { 0.0f,1.0f,0.0f });

	//����ĳһ����۲�
	void LookTo(const XMFLOAT3& direction, const XMFLOAT3& up = { 0.0f,1.0f,0.0f });

public:
	//����ת�����л�ȡŷ����
	XMFLOAT3 GetEulerAnglesFromRotationMatrix(const XMFLOAT4X4& rotationMatrix);

public:
	XMFLOAT3 m_Scale = { 1.0f,1.0f,1.0f };    //����
	XMFLOAT3 m_Rotation = {};                  //��תŷ����(������)
	XMFLOAT3 m_Position = {};                  //λ��
};

