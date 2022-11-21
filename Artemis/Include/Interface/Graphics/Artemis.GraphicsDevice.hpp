﻿#pragma once

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#include "Artemis.GraphicsTypes.hpp"
#include "../Artemis.Interface.hpp"
#include "Artemis.Buffer.hpp"

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
namespace Artemis
{
namespace Graphics
{

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
class IGraphicsDevice
{
protected:
	IGraphicsDevice() { }
	virtual ~IGraphicsDevice() { }

public:
	virtual SizeI GetBackBufferSize() = 0;
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
}
}
