//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#include "Artemis.Local.hpp"

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
namespace Artemis
{
namespace System
{
namespace Platform
{

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
static struct Global
{
	HWND hWindow;
}
_Global;

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:		//====================== ウィンドウ生成
		::timeBeginPeriod(1);
		break;
	case WM_CLOSE:		//====================== ウィンドウを閉じる
		::timeEndPeriod(1);
		break;
	case WM_ACTIVATE:	//====================== ウィンドウのアクティブ化、非アクティブ化の通知
		switch (wParam)
		{
		case WA_INACTIVE:	// 非アクティブ化されます。
			break;
		case WA_ACTIVE:		// マウスクリック以外の方法でアクティブ化されます。
		case WA_CLICKACTIVE:// マウスクリックによってアクティブ化されます。
			break;
		}
		break;
	case WM_DESTROY:	//====================== ウィンドウ破棄
		::PostQuitMessage(0);
		return 0;
	}

	// 自分で処理しないメッセージ
	return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
bool Initialize(const wchar_t ApplicationName[], SizeI ScreenSize, int32_t FrameRate)
{
	auto hInstance = ::GetModuleHandle(nullptr);

	//------------------------------------------------------------
	// ウィンドウクラス生成
	//------------------------------------------------------------
	WNDCLASSW WindowClass;
	WindowClass.style = CS_HREDRAW | CS_VREDRAW;
	WindowClass.lpfnWndProc = WndProc;
	WindowClass.cbClsExtra = 0;
	WindowClass.cbWndExtra = 0;
	WindowClass.hInstance = hInstance;
	WindowClass.hIcon = nullptr;
	WindowClass.hCursor = ::LoadCursor(nullptr, IDC_ARROW);
	WindowClass.hbrBackground = (HBRUSH)::GetStockObject(BLACK_BRUSH);
	WindowClass.lpszMenuName = nullptr;
	WindowClass.lpszClassName = ApplicationName;
	::RegisterClass(&WindowClass);

	//------------------------------------------------------------
	// ウィンドウ生成
	//------------------------------------------------------------
	int32_t x = 0;
	int32_t y = 0;
	int32_t w = ScreenSize.W;
	int32_t h = ScreenSize.H;
	int32_t Style = WS_POPUP | WS_CAPTION | WS_SYSMENU | WS_EX_ACCEPTFILES;
	RECT Rect = { 0, 0, w, h };
	::AdjustWindowRect(&Rect, Style, FALSE);
	w = Rect.right - Rect.left;
	h = Rect.bottom - Rect.top;
	x = ::GetSystemMetrics(SM_CXSCREEN) / 2 - w / 2;
	y = ::GetSystemMetrics(SM_CYSCREEN) / 2 - h / 2;

	_Global.hWindow = ::CreateWindowEx(
		WS_EX_ACCEPTFILES | WS_EX_APPWINDOW,
		ApplicationName,
		ApplicationName,
		Style,
		x, y, w, h,
		nullptr,
		nullptr,
		hInstance,
		nullptr);

	::ShowWindow(_Global.hWindow, SW_NORMAL);
	::UpdateWindow(_Global.hWindow);

	return true;
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
void Uninitialize()
{
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
bool Update()
{
	auto MsgProc = []() {
		MSG Msg;
		while (::PeekMessage(&Msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (Msg.message == WM_QUIT)
			{
				return false;
			}
			::TranslateMessage(&Msg);
			::DispatchMessage(&Msg);
		}
		return true;
	};

	return MsgProc();
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
void* GetWindowHandle()
{
	return _Global.hWindow;
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
PointI GetCursorPosition()
{
	POINT Point;
	::GetCursorPos(&Point);
	::ScreenToClient(_Global.hWindow, &Point);

	return PointI(Point.x, Point.y);
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
}
}
}
