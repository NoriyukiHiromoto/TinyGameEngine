#pragma once

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#include <Interface/System/Artemis.SystemInfo.hpp>
#include "Common/Artemis.SingletonObject.hpp"
#include "Common/Artemis.FrameTime.hpp"

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
namespace Artemis
{
namespace System
{

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
class SystemInfo
	: public ISystemInfo
	, public Common::SingletonObject
	, public Common::Singleton<SystemInfo>
{
	friend class Common::Singleton<SystemInfo>;

private:
	Common::FrameTime _FrameTime;

public:
	bool Initialize();
	void Uninitialize();

	virtual const Common::IFrameTime* FrameTime() const override { return &_FrameTime; }
	virtual Common::FrameTime& RefFrameTime() { return _FrameTime; }
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
}
}
