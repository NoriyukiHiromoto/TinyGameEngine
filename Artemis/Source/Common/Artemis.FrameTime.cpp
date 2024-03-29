﻿//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#include "Common/Artemis.FrameTime.hpp"

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
FrameTime::FrameTime()
	: _Start(std::chrono::high_resolution_clock::now())
{
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
FrameTime::~FrameTime()
{
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
void FrameTime::Update()
{
	auto Now = std::chrono::high_resolution_clock::now();
	auto Elapsed = std::chrono::duration_cast<std::chrono::microseconds>(Now - _Start).count();
	_Start = Now;

	_UnscaledDeltaTime = static_cast<float_t>(static_cast<double_t>(Elapsed) / 1000000.0);
	_DeltaTime = _UnscaledDeltaTime * _TimeScale;
	_GameTime += _UnscaledDeltaTime;
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
void FrameTime::Reset()
{
	_Start = std::chrono::high_resolution_clock::now();

	_TimeScale = 1.0f;
	_GameTime = 0.0f;
	_DeltaTime = 0.0f;
	_UnscaledDeltaTime = 0.0f;
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
}
}
