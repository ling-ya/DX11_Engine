#pragma once
#include<vector>
#include"Singleton.h"
#include"GameObject.h"

class ObjectManager :public Singleton<ObjectManager>
{
public:
	ObjectManager();
	void AddObj(GameObject* pObj);
	void DoFrame(float deltaTime);
	GameObject* GetObj(string name);
private:
	vector<GameObject*> m_objList;
};

