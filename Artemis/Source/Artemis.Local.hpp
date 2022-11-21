#pragma once

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#if defined(ATS_WINDOWS)
	#define NOMINMAX
	#define WIN32_LEAN_AND_MEAN
	#define _CRT_SECURE_NO_WARNINGS
	#define _CRT_NON_CONFORMING_SWPRINTFS
	#include <windows.h>
	#include <mmsystem.h>
#endif//defined(ATS_WINDOWS)

#if defined(ATS_API_DIRECTX11)
	#include <dxgi.h>
	#include <d3d11.h>
	#include <d3dcompiler.h>
#endif//defined(ATS_API_DIRECTX11)

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#include <stdio.h>
#include <cmath>
#include <thread>
#include <atomic>
#include <vector>
#include <map>

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#include "Artemis.hpp"

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#define ATS_STRING_MERGE(A, B)			A##B

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#if defined(ATS_DEBUG)
inline void DebugOutput(const char* format, ...)
{
	char message[4096] = "";

	va_list va;
	va_start(va, format);
	vsprintf_s(message, sizeof(message), format, va);
	va_end(va);

	::OutputDebugStringA("[ARTEMIS] ");
	::OutputDebugStringA(message);

	printf("[ARTEMIS] %s", message);
}
#define ATS_PRINT(...)			{ DebugOutput(__VA_ARGS__); }
#define ATS_HALT(...)			{ DebugOutput(__VA_ARGS__); (*((uint32_t*)0x0) = 0x0); }
#define ATS_MESSAGE(_MESSAGE_)																	\
{																								\
	printf("%s(%u) [%s] %s\n", __FILE__, __LINE__, __FUNCTION__, _MESSAGE_);					\
	char ___temp___[1024] = "";																	\
	sprintf_s(___temp___, sizeof(___temp___), "%s(%u)\n%s", __FILE__, __LINE__, _MESSAGE_);		\
	::MessageBoxA(::GetActiveWindow(), ___temp___, "Message", MB_ICONSTOP);						\
}
#define ATS_ASSERT(_EXPRESSION_, _MESSAGE_)														\
{																								\
	if (!(_EXPRESSION_))																		\
	{																							\
		printf("%s(%u) [%s] %s\n", __FILE__, __LINE__, __FUNCTION__, _MESSAGE_);				\
		char ___temp___[1024] = "";																\
		sprintf_s(___temp___, sizeof(___temp___), "%s(%u)\n%s", __FILE__, __LINE__, _MESSAGE_);	\
		::MessageBoxA(::GetActiveWindow(), ___temp___, "Error", MB_ICONSTOP);					\
		(*((uint32_t*)0x0) = 0x0);																\
	}																							\
}
#else//ATS_DEBUG
#define ATS_PRINT(...)
#define ATS_HALT(...)
#define ATS_MESSAGE(_MESSAGE_)
#define ATS_ASSERT(_EXPRESSION_, _MESSAGE_)
#endif//defined(ATS_DEBUG)

#define ATS_STATIC_ASSERT(_EXPRESSION_, _MESSAGE_)	static_assert(_EXPRESSION_, _MESSAGE_)
