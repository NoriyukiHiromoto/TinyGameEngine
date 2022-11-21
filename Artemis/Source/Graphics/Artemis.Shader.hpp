#pragma once

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#include <Interface/Graphics/Artemis.Shader.hpp>
#include "Common/Artemis.ReferenceCountObject.hpp"

#if defined(ATS_API_DIRECTX11)
#include "Platform/Artemis.Shader.directx11.hpp"
#endif//defined(ATS_API_DIRECTX11)
