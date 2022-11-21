#pragma once

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#include "Artemis.Local.hpp"

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
class MemoryObject
{
protected:
	MemoryObject() {}
	~MemoryObject() {}

public:
	void* operator new (size_t size);
	void* operator new (size_t size, const std::nothrow_t&);
	void* operator new[](size_t size);
	void* operator new[](size_t size, const std::nothrow_t&);
	void* operator new (size_t size, const char* pFile, uint32_t Line);
	void* operator new (size_t size, const std::nothrow_t&, const char* pFile, uint32_t Line);
	void* operator new[](size_t size, const char* pFile, uint32_t Line);
	void* operator new[](size_t size, const std::nothrow_t&, const char* pFile, uint32_t Line);

	void operator delete (void* address);
	void operator delete (void* address, const std::nothrow_t&);
	void operator delete[](void* address);
	void operator delete[](void* address, const std::nothrow_t&);
	void operator delete (void* address, const char* pFile, uint32_t Line);
	void operator delete (void* address, const std::nothrow_t&, const char* pFile, uint32_t Line);
	void operator delete[](void* address, const char* pFile, uint32_t Line);
	void operator delete[](void* address, const std::nothrow_t&, const char* pFile, uint32_t Line);
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
class VirtualMemoryObject
{
protected:
	VirtualMemoryObject() {}
	virtual ~VirtualMemoryObject() {}

public:
	void* operator new (size_t size);
	void* operator new (size_t size, const std::nothrow_t&);
	void* operator new[](size_t size);
	void* operator new[](size_t size, const std::nothrow_t&);
	void* operator new (size_t size, const char* pFile, uint32_t Line);
	void* operator new (size_t size, const std::nothrow_t&, const char* pFile, uint32_t Line);
	void* operator new[](size_t size, const char* pFile, uint32_t Line);
	void* operator new[](size_t size, const std::nothrow_t&, const char* pFile, uint32_t Line);

	void operator delete (void* address);
	void operator delete (void* address, const std::nothrow_t&);
	void operator delete[](void* address);
	void operator delete[](void* address, const std::nothrow_t&);
	void operator delete (void* address, const char* pFile, uint32_t Line);
	void operator delete (void* address, const std::nothrow_t&, const char* pFile, uint32_t Line);
	void operator delete[](void* address, const char* pFile, uint32_t Line);
	void operator delete[](void* address, const std::nothrow_t&, const char* pFile, uint32_t Line);
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#define ATS_NEW new(__FILE__, __LINE__)

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
}
}
