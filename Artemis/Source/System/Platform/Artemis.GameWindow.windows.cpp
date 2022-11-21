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
			//::ReleaseCapture();
			break;
		case WA_ACTIVE:		// マウスクリック以外の方法でアクティブ化されます。
		case WA_CLICKACTIVE:// マウスクリックによってアクティブ化されます。
			//::SetCapture(hWnd);
			break;
		}
		break;
	case WM_SIZE:
		{
			const auto SizeType = wParam;					// フラグ
			const auto Width    = lParam & 0xFFFF;			// xサイズ
			const auto Height   = (lParam >> 16) & 0xFFFF;	// yサイズ
			GameWindow::Instance()->SizeChanged(SizeI((int32_t)Width, (int32_t)Height));
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
bool GameWindow::Initialize(const wchar_t ApplicationName[], SizeI ScreenSize)
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
	int32_t Style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_EX_ACCEPTFILES | WS_THICKFRAME;
	RECT Rect = { 0, 0, w, h };
	::AdjustWindowRect(&Rect, Style, FALSE);
	w = Rect.right - Rect.left;
	h = Rect.bottom - Rect.top;
	x = ::GetSystemMetrics(SM_CXSCREEN) / 2 - w / 2;
	y = ::GetSystemMetrics(SM_CYSCREEN) / 2 - h / 2;

	_hWindow = ::CreateWindowEx(
		WS_EX_ACCEPTFILES | WS_EX_APPWINDOW,
		ApplicationName,
		ApplicationName,
		Style,
		x, y, w, h,
		nullptr,
		nullptr,
		hInstance,
		nullptr);

	::ShowWindow(_hWindow, SW_NORMAL);
	::UpdateWindow(_hWindow);

	_IsOpen = true;

	return true;
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
void GameWindow::Uninitialize()
{
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
void GameWindow::WaitClose()
{
	MSG Msg;
	while (::GetMessage(&Msg, nullptr, 0, 0))
	{
		::TranslateMessage(&Msg);
		::DispatchMessage(&Msg);
	}

	_IsOpen = false;
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
void GameWindow::RequireClose()
{
	::PostMessage(_hWindow, WM_CLOSE, 0, 0);
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
void GameWindow::SizeChanged(SizeI NewSize)
{
	_WindowSizeChangedLastTime = ::timeGetTime();
	_WindowSize = NewSize;
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
void* GameWindow::GetWindowHandle() const
{
	return _hWindow;
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
SizeI GameWindow::GetWindowSize() const
{
	return _WindowSize;
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
bool GameWindow::IsWindowResizing() const
{
	return (::timeGetTime() - _WindowSizeChangedLastTime) < 250;
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
bool GameWindow::IsOpen() const
{
	return _IsOpen;
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
//PointI GetCursorPosition()
//{
//	POINT Point;
//	::GetCursorPos(&Point);
//	::ScreenToClient(_hWindow, &Point);
//
//	return PointI(Point.x, Point.y);
//}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
}
}
