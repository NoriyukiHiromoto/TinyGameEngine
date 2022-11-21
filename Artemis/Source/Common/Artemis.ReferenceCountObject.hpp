#pragma once

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#include "Common/Artemis.Object.hpp"

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
namespace Artemis
{
namespace Common
{

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
class ReferenceCountObject
	: public VirtualMemoryObject
{
private:
	ReferenceCountObject(const ReferenceCountObject& value);
	ReferenceCountObject& operator = (const ReferenceCountObject& value);

private:
	std::atomic_int32_t	_ReferenceCount;

protected:
	ReferenceCountObject();
	virtual ~ReferenceCountObject();

public:
	virtual int32_t AddReference();
	virtual int32_t Release();
	virtual int32_t GetReference() const;
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
}
}
