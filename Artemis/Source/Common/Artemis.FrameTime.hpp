#pragma once

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#include <Interface/Common/Artemis.FrameTime.hpp>
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
class FrameTime
	: public MemoryObject
	, public IFrameTime
{
private:
	std::chrono::high_resolution_clock::time_point _Start;
	float_t _GameTime;
	float_t _DeltaTime;
	float_t _UnscaledDeltaTime;
	float_t _TimeScale;

public:
	FrameTime();
	virtual ~FrameTime();

	void Update();
	void Reset();

public:
	virtual float_t GameTime() const override { return _GameTime; }
	virtual float_t DeltaTime() const override { return _DeltaTime; }
	virtual float_t UnscaledDeltaTime() const override { return _UnscaledDeltaTime; }

	virtual void SetTimeScale(float_t scale) override { _TimeScale = scale; }
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
}
}
