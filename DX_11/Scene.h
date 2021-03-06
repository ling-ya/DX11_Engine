#pragma once
#include"Window.h"
#include"Mouse.h"
#include"keyBoard.h"
#include "GameObject.h"
#include "Mesh.h"
#include "MeshRender.h"
#include "Light.h"
#include "Camera.h"
#include "Transform.h"
class Scene
{
public:
	Scene();
	~Scene() = default;
	void Init();
	void UpdateScene(float deltaTime);
	void UpdateReflectState();
	void UpdateNormalState();
	
public:
	Window* m_pWindow;
	DirectX::Mouse::ButtonStateTracker MouseTracker;				// ????״̬׷????
	DirectX::Keyboard::KeyboardStateTracker KeyboardTracker;		// ????״̬׷????

public:
	GameObject* m_pLight;                                      //?ƹ?
	GameObject* m_pCamera;                                     //????

	//??͸??????
	GameObject* m_pCube;
	GameObject* m_pPlane;
	vector<GameObject*> m_Walls;

	//͸??????
	GameObject* m_WireFence;
	GameObject* m_water;

	//???侵??
	GameObject* m_Mirror;
};

