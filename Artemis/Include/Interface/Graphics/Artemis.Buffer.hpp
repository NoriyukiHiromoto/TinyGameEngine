﻿#pragma once

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#include "Artemis.GraphicsTypes.hpp"
#include "../Artemis.Interface.hpp"

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
class IBuffer
	: public Interface
{
protected:
	IBuffer() { }
	virtual ~IBuffer() { }

public:
	virtual eBufferType BufferType() const = 0;
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
}
}