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

public:
	Window* m_pWindow;
	DirectX::Mouse::ButtonStateTracker MouseTracker;				// 鼠标状态追踪器
	DirectX::Keyboard::KeyboardStateTracker KeyboardTracker;		// 键盘状态追踪器

public:
	GameObject* m_pLight;                                      //灯光
	GameObject* m_pCamera;                                     //相机

	//不透明物体
	GameObject* m_pCube;
	GameObject* m_pPlane;
	vector<GameObject*> m_Walls;

	//透明物体
	GameObject* m_WireFence;
	GameObject* m_water;
};

