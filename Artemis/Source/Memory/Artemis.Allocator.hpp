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
namespace Memory
{

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
class Allocator
{
	struct MemoryBlock
	{
		uint32_t Size;
		uint32_t Line;
		const char* pFileName;
	};

private:
	static uint32_t _MemorySizeInUse;

public:
	static bool Initialize();
	static void Uninitialize();

	static void* Malloc(uint32_t Size, const char* pFileName, const uint32_t Line);
	static void Free(void* pMemory);

	static uint32_t GetMemorySizeInUse() { return _MemorySizeInUse; }
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
}
}
