#pragma once

template<class T>
class Singleton
{
public:
	static T* Instance() 
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new T();
		}
		return m_pInstance;
	}

private:
	static T* m_pInstance;
};

template<class T>
T* Singleton<T>::m_pInstance = nullptr;

