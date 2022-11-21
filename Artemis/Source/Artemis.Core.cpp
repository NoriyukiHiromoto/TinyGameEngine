//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#include "Artemis.Local.hpp"

#include "Memory/Artemis.Allocator.hpp"

#include "System/Artemis.GameWindow.hpp"
#include "System/Artemis.SystemInfo.hpp"
#include "Graphics/Artemis.GraphicsDevice.hpp"

#include "Threading/Artemis.Thread.hpp"

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

	// アロケーター初期化
	if (Memory::Allocator::Initialize())
	{
		// ウインドウ生成
		if (System::GameWindow::CreateInstance([&](System::GameWindow* pSrc) { return pSrc->Initialize(ApplicationName, ScreenSize); }))
		{
			void* hWindow = System::GameWindow::Instance()->GetWindowHandle();

			// ゲームスレッド生成
			Threading::Thread GameThread(
				[=, &bSucceeded](void*) {
					auto CreateInstanceAll = [=]() {
						if (!System::SystemInfo::CreateInstance([&](System::SystemInfo* pSrc) { return pSrc->Initialize(); })) return false;
						if (!Graphics::GraphicsDevice::CreateInstance([&](Graphics::GraphicsDevice* pSrc) { return pSrc->Initialize(hWindow, ScreenSize); }))return false;
						return true;
					};
					auto ReleaseInstanceAll = [=]() {
						Graphics::GraphicsDevice::Instance()->ReleaseInstance([](Graphics::GraphicsDevice* pSrc) { pSrc->Uninitialize(); });
						System::SystemInfo::ReleaseInstance([](System::SystemInfo* pSrc) { pSrc->Uninitialize(); });
					};

					// シングルトン全部初期化
					if (CreateInstanceAll())
					{
						// ゲーム時間のリセット
						System::SystemInfo::Instance()->RefFrameTime().Reset();
						// メイン関数呼び出し
						bSucceeded = MainProc();
					}
					// シングルトン全部終了
					ReleaseInstanceAll();

					// ウインドウ削除リクエスト
					System::GameWindow::Instance()->RequireClose();
				},
				nullptr);

			// ウインドウ閉じるまで待つ
			System::GameWindow::Instance()->WaitClose();

			// ゲームスレッド終わるまで待つ
			GameThread.Wait();
		}

		// ゲームウインドウ終了
		System::GameWindow::ReleaseInstance([](System::GameWindow* pSrc) { pSrc->Uninitialize(); });
	}

	// アロケ―ター終了
	Memory::Allocator::Uninitialize();

	return bSucceeded;
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
bool Update()
{
	// 画面の更新
	Graphics::GraphicsDevice::Instance()->Present();

	// ウインドウサイズの変更チェック
	auto NewSize = System::GameWindow::Instance()->GetWindowSize();
	auto CurrentSize = Graphics::GraphicsDevice::Instance()->GetBackBufferSize();
	if (NewSize != CurrentSize)
	{
		// ウインドウサイズ変更途中じゃない時
		if (!System::GameWindow::Instance()->IsWindowResizing())
		{
			// スワップチェインを作り直す
			Graphics::GraphicsDevice::Instance()->CreateSwapChain(NewSize);
		}
	}

	// バックバッファのクリア
#if false
	static ColorF ClearColor(ColorF::GRAY);
	ClearColor.R += 0.7f * System::SystemInfo::Instance()->FrameTime()->UnscaledDeltaTime();
	ClearColor.G += 0.6f * System::SystemInfo::Instance()->FrameTime()->UnscaledDeltaTime();
	ClearColor.B += 0.5f * System::SystemInfo::Instance()->FrameTime()->UnscaledDeltaTime();
	if (ClearColor.R > 1.0f) ClearColor.R -= 0.8f;
	if (ClearColor.G > 1.0f) ClearColor.G -= 0.8f;
	if (ClearColor.B > 1.0f) ClearColor.B -= 0.8f;
	Graphics::GraphicsDevice::Instance()->ClearBackBuffer(ClearColor);
#else//defined(ATS_DEBUG)
	Graphics::GraphicsDevice::Instance()->ClearBackBuffer(ColorF::BLACK);
#endif//defined(ATS_DEBUG)

	// ゲーム時間の更新
	System::SystemInfo::Instance()->RefFrameTime().Update();

	// ウインドウがある限り継続
	return System::GameWindow::Instance()->IsOpen();
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
System::ISystemInfo* GetSystemInfo()
{
	return System::SystemInfo::Instance();
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
Graphics::IGraphicsDevice* GetGraphicsDevice()
{
	return Graphics::GraphicsDevice::Instance();
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
}
}
