#pragma once

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
namespace Artemis
{
namespace Graphics
{

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
class GraphicsDevice
	: public IGraphicsDevice
	, public Common::SingletonObject
	, public Common::Singleton<GraphicsDevice>
{
	friend class Common::Singleton<GraphicsDevice>;

private:
	IDXGIDevice1* _pDXGIDevice;
	IDXGIAdapter* _pDXGIAdapter;
	IDXGIFactory* _pDXGIFactory;
	ID3D11Device* _pDevice;
	ID3D11DeviceContext* _pDeviceContext;
	IDXGISwapChain* _pSwapChain;
	ID3D11Texture2D* _pBackBufferTexture;
	ID3D11RenderTargetView* _pBackBufferRenderTargetView;
	void* _WindowHandle;
	SizeI _BackBufferSize;

public:
	bool Initialize(void* pWindowHandle, SizeI ScreenSize);
	void Uninitialize();
	bool CreateSwapChain(SizeI ScreenSize);
	void ClearBackBuffer(const ColorF& Color);
	void Present();

public:
	virtual SizeI GetBackBufferSize() override;
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
}
}
