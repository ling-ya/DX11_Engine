#include "ObjectManager.h"

ObjectManager::ObjectManager()
{
}

void ObjectManager::AddObj(GameObject* pObj)
{
	m_objList.push_back(pObj);
}

void ObjectManager::DoFrame(float deltaTime)
{
	for (UINT i = 0; i < m_objList.size(); i++)
	{
		if (m_objList[i] != nullptr)
		{
			m_objList[i]->Update(deltaTime);
		}
	}
}

GameObject* ObjectManager::GetObj(string name)
{
	return nullptr;
}
