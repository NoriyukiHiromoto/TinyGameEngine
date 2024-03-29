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
class IShaderBinary
	: public Interface
{
protected:
	IShaderBinary() { }
	virtual ~IShaderBinary() { }

public:
	virtual const void* GetCodePointer() const = 0;
	virtual uint32_t GetCodeSize() const = 0;
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
}
}
