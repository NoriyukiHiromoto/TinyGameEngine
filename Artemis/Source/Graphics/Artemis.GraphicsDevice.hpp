#pragma once

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#include <Interface/Graphics/Artemis.GraphicsDevice.hpp>
#include "Common/Artemis.SingletonObject.hpp"

#if defined(ATS_API_DIRECTX11)
#include "Platform/Artemis.GraphicsDevice.directx11.hpp"
#endif//defined(ATS_API_DIRECTX11)
