#pragma once
#include"Graphics.h"
#include"GameObject.h"


class Component
{
public:
	Component();
	~Component() = default;
	virtual void Start();
	virtual void Update(float deltaTime);

public:
	GameObject* m_pObject;
};

