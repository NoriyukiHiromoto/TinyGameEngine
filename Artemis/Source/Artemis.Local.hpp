//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#include <stdio.h>

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
#endif//defined(ATS_API_DIRECTX11)

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#include "Artemis.hpp"
