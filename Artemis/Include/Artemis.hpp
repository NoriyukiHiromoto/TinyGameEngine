#pragma once

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#if defined(ATS_WINDOWS)
	#pragma comment(lib, "winmm.lib")
#endif//defined(ATS_WINDOWS)
#if defined(ATS_API_DIRECTX11)
	#pragma comment(lib, "d3d11.lib")
#endif//defined(ATS_API_DIRECTX11)

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#include "Artemis.Types.hpp"

#include "Artemis.Core.hpp"
