#pragma once

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#include "Common/Artemis.Object.hpp"

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
namespace Artemis
{
namespace Common
{

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
class SingletonObject
	: public VirtualMemoryObject
{
private:
	SingletonObject& operator = (const SingletonObject& rhs);

public:
	SingletonObject() {}
	virtual ~SingletonObject() {}
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
template <typename T>
class Singleton
{
private:
	static T* _pInstance;

protected:
	Singleton() { }
	virtual ~Singleton() { }

public:
	static bool CreateInstance(std::function<bool(T* pInstance)> Callback)
	{
		ATS_ASSERT(_pInstance == nullptr, "既に初期化済みのインスタンスです");
		_pInstance = new T();
		return (_pInstance == nullptr) ? false : Callback(_pInstance);
	}

	static void ReleaseInstance(std::function<void(T* pInstance)> Callback)
	{
		if (_pInstance != nullptr)
		{
			Callback(_pInstance);
			delete _pInstance;
			_pInstance = nullptr;
		}
	}

	static T* Instance()
	{
		return _pInstance;
	}
};

template <typename T> T* Singleton<T>::_pInstance = nullptr;

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
}
}
