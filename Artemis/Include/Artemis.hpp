#pragma once

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#if defined(ATS_WINDOWS)
	#pragma comment(lib, "winmm.lib")
#endif//defined(ATS_WINDOWS)

#if defined(ATS_API_DIRECTX11)
	#pragma comment(lib, "d3d11.lib")
	#pragma comment(lib, "d3dcompiler.lib")
#endif//defined(ATS_API_DIRECTX11)

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#define ATS_SAFE_DELETE(value)			{ if ( value != nullptr ) { delete value; value = nullptr; } }
#define ATS_SAFE_DELETE_ARRAY(value)	{ if ( value != nullptr ) { delete [] value; value = nullptr; } }
#define ATS_SAFE_ADDREFERENCE(value)	{ if ( value != nullptr ) { value->AddReference(); } }
#define ATS_SAFE_ADDREF(value)			{ if ( value != nullptr ) { value->AddRef(); } }
#define ATS_SAFE_RELEASE(value)			{ if ( value != nullptr ) { value->Release(); value = nullptr; } }
#define ATS_SHADER_CODE(code)			#code

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#include "Artemis.Types.hpp"

#include "Math/Artemis.VectorUtil.hpp"
#include "Math/Artemis.MatrixUtil.hpp"

#include "Interface/Common/Artemis.FrameTime.hpp"

#include "Interface/System/Artemis.SystemInfo.hpp"

#include "Interface/Graphics/Artemis.GraphicsTypes.hpp"
#include "Interface/Graphics/Artemis.Buffer.hpp"
#include "Interface/Graphics/Artemis.GraphicsDevice.hpp"

#include "Artemis.Core.hpp"
