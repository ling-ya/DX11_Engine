#pragma once
#include<vector>
#include <wtypes.h>
#include <string>
#include<functional>

using namespace std;

class Component;
class GameObject
{
public:
	GameObject();
	~GameObject() = default;

	void Update(float deltaTime);
	static GameObject* CreateGameObject(string name);
	void AddComponent(Component* pComponent);

	template<class T>
	T* GetComponent();

public:
	vector<Component*> m_componentList;
	string name;
};


template<class T>
inline T* GameObject::GetComponent()
{
	for (UINT i = 0; i < m_componentList.size(); i++)
	{
		if (m_componentList[i] != nullptr && (typeid(*m_componentList[i]) == typeid(T)))
		{
			return (T*)m_componentList[i];
		}
	}
	return nullptr;
}

