//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#include "Common/Artemis.Object.hpp"
#include "Memory/Artemis.Allocator.hpp"

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
void* MemoryObject::operator new (size_t size)
{
	return Memory::Allocator::Malloc(static_cast<uint32_t>(size), __FILE__, __LINE__);
}
void* MemoryObject::operator new (size_t size, const std::nothrow_t&)
{
	return Memory::Allocator::Malloc(static_cast<uint32_t>(size), __FILE__, __LINE__);
}
void* MemoryObject::operator new [](size_t size)
{
	return Memory::Allocator::Malloc(static_cast<uint32_t>(size), __FILE__, __LINE__);
}
void* MemoryObject::operator new [](size_t size, const std::nothrow_t&)
{
	return Memory::Allocator::Malloc(static_cast<uint32_t>(size), __FILE__, __LINE__);
}
void* MemoryObject::operator new (size_t size, const char* pFile, uint32_t Line)
{
	return Memory::Allocator::Malloc(static_cast<uint32_t>(size), pFile, Line);
}
void* MemoryObject::operator new (size_t size, const std::nothrow_t&, const char* pFile, uint32_t Line)
{
	return Memory::Allocator::Malloc(static_cast<uint32_t>(size), pFile, Line);
}
void* MemoryObject::operator new [](size_t size, const char* pFile, uint32_t Line)
{
	return Memory::Allocator::Malloc(static_cast<uint32_t>(size), pFile, Line);
}
void* MemoryObject::operator new [](size_t size, const std::nothrow_t&, const char* pFile, uint32_t Line)
{
	return Memory::Allocator::Malloc(static_cast<uint32_t>(size), pFile, Line);
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
void MemoryObject::operator delete (void* address)
{
	Memory::Allocator::Free(address);
}
void MemoryObject::operator delete (void* address, const std::nothrow_t&)
{
	Memory::Allocator::Free(address);
}
void MemoryObject::operator delete [](void* address)
{
	Memory::Allocator::Free(address);
}
void MemoryObject::operator delete [](void* address, const std::nothrow_t&)
{
	Memory::Allocator::Free(address);
}
void MemoryObject::operator delete (void* address, const char*, uint32_t)
{
	Memory::Allocator::Free(address);
}
void MemoryObject::operator delete (void* address, const std::nothrow_t&, const char*, uint32_t)
{
	Memory::Allocator::Free(address);
}
void MemoryObject::operator delete [](void* address, const char*, uint32_t)
{
	Memory::Allocator::Free(address);
}
void MemoryObject::operator delete [](void* address, const std::nothrow_t&, const char*, uint32_t)
{
	Memory::Allocator::Free(address);
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
void* VirtualMemoryObject::operator new (size_t size)
{
	return Memory::Allocator::Malloc(static_cast<uint32_t>(size), __FILE__, __LINE__);
}
void* VirtualMemoryObject::operator new (size_t size, const std::nothrow_t&)
{
	return Memory::Allocator::Malloc(static_cast<uint32_t>(size), __FILE__, __LINE__);
}
void* VirtualMemoryObject::operator new [](size_t size)
{
	return Memory::Allocator::Malloc(static_cast<uint32_t>(size), __FILE__, __LINE__);
}
void* VirtualMemoryObject::operator new [](size_t size, const std::nothrow_t&)
{
	return Memory::Allocator::Malloc(static_cast<uint32_t>(size), __FILE__, __LINE__);
}
void* VirtualMemoryObject::operator new (size_t size, const char* pFile, uint32_t Line)
{
	return Memory::Allocator::Malloc(static_cast<uint32_t>(size), pFile, Line);
}
void* VirtualMemoryObject::operator new (size_t size, const std::nothrow_t&, const char* pFile, uint32_t Line)
{
	return Memory::Allocator::Malloc(static_cast<uint32_t>(size), pFile, Line);
}
void* VirtualMemoryObject::operator new [](size_t size, const char* pFile, uint32_t Line)
{
	return Memory::Allocator::Malloc(static_cast<uint32_t>(size), pFile, Line);
}
void* VirtualMemoryObject::operator new [](size_t size, const std::nothrow_t&, const char* pFile, uint32_t Line)
{
	return Memory::Allocator::Malloc(static_cast<uint32_t>(size), pFile, Line);
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
void VirtualMemoryObject::operator delete (void* address)
{
	Memory::Allocator::Free(address);
}
void VirtualMemoryObject::operator delete (void* address, const std::nothrow_t&)
{
	Memory::Allocator::Free(address);
}
void VirtualMemoryObject::operator delete [](void* address)
{
	Memory::Allocator::Free(address);
}
void VirtualMemoryObject::operator delete [](void* address, const std::nothrow_t&)
{
	Memory::Allocator::Free(address);
}
void VirtualMemoryObject::operator delete (void* address, const char*, uint32_t)
{
	Memory::Allocator::Free(address);
}
void VirtualMemoryObject::operator delete (void* address, const std::nothrow_t&, const char*, uint32_t)
{
	Memory::Allocator::Free(address);
}
void VirtualMemoryObject::operator delete [](void* address, const char*, uint32_t)
{
	Memory::Allocator::Free(address);
}
void VirtualMemoryObject::operator delete [](void* address, const std::nothrow_t&, const char*, uint32_t)
{
	Memory::Allocator::Free(address);
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
}
}
