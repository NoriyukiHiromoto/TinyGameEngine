﻿#pragma once

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#include "../Artemis.Types.hpp"

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
namespace Artemis
{

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
class Interface
{
protected:
	Interface() {}
	virtual ~Interface() {}

public:
	virtual int32_t AddReference() = 0;
	virtual int32_t Release() = 0;
	virtual int32_t GetReference() const = 0;
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
}