//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#include "Artemis.Local.hpp"

#include "System/Artemis.System.hpp"
#include "Graphics/Artemis.Graphics.hpp"

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
namespace Artemis
{
namespace Core
{

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
bool Bootup(const wchar_t ApplicationName[], SizeI ScreenSize, int32_t FrameRate, std::function<bool(void)> MainProc)
{
	bool bSucceeded = false;

	if (System::Initialize(ApplicationName, ScreenSize, FrameRate))
	{
		if (Graphics::Initialize(System::GetWindowHandle(), ScreenSize))
		{
			Graphics::Clear();
			bSucceeded = MainProc();
		}

		Graphics::Uninitialize();
	}

	System::Uninitialize();

	return bSucceeded;
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
bool Update()
{
	if (!System::Update())
	{
		return false;
	}

	Graphics::Present();

	Graphics::Clear();

	return true;
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
}
}
