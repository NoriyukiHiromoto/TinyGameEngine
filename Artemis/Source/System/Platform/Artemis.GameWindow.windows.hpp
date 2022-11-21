#pragma once

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
class GameWindow
	: public Common::SingletonObject
	, public Common::Singleton<GameWindow>
{
	friend class Common::Singleton<GameWindow>;

private:
	HWND _hWindow;
	bool _IsOpen;
	SizeI _WindowSize;
	uint32_t _WindowSizeChangedLastTime;

public:
	bool Initialize(const wchar_t ApplicationName[], SizeI ScreenSize);
	void Uninitialize();
	void WaitClose();
	void RequireClose();
	void SizeChanged(SizeI NewSize);
	void* GetWindowHandle() const;
	SizeI GetWindowSize() const;
	bool IsWindowResizing() const;
	bool IsOpen() const;
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
}
}
