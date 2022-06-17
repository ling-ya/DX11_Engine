#include "GameObject.h"
#include"ObjectManager.h"
#include"Transform.h"

GameObject::GameObject()
{

}
void GameObject::Update(float deltaTime)
{
	for (UINT i = 0; i < m_componentList.size(); i++)
	{
		if (m_componentList[i] != nullptr)
		{
			m_componentList[i]->Update(deltaTime);
		}
	}
}

GameObject* GameObject::CreateGameObject(string name)
{
	GameObject* pGO = new GameObject();
	pGO->name = name;
	pGO->AddComponent(new Transform());
	ObjectManager::Instance()->AddObj(pGO);
	return pGO;
}

void GameObject::AddComponent(Component* pComponent)
{
	if (pComponent != nullptr)
	{
		pComponent->m_pObject = this;
		pComponent->Start();
		m_componentList.push_back(pComponent);
	}
}
