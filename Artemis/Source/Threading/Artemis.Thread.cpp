﻿//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#include "Artemis.Thread.hpp"

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
namespace Artemis
{
namespace Threading
{

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
Thread::Thread()
{
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
Thread::Thread(std::function<void(void*)> Callback, void* pParameter)
{
	Create(Callback, pParameter);
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
void Thread::Create(std::function<void(void*)> Callback, void* pParameter)
{
	Wait();

	_Callback = Callback;
	_pParameter = pParameter;

	_Thread = std::thread([this]() {
		_Callback(_pParameter);
	});
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
void Thread::Wait()
{
	if (_Thread.joinable())
	{
		_Thread.join();
	}
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
void Thread::Sleep(uint32_t MilliSecoond)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(MilliSecoond));
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
}
}
