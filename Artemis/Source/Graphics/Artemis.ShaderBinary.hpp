#pragma once

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#include <Interface/Graphics/Artemis.ShaderBinary.hpp>
#include "Common/Artemis.ReferenceCountObject.hpp"

#if defined(ATS_API_DIRECTX11)
#include "Platform/Artemis.ShaderBinary.directx11.hpp"
#endif//defined(ATS_API_DIRECTX11)
