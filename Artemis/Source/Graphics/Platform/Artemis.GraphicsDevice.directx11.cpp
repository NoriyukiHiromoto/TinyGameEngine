
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
bool GraphicsDevice::Initialize(void* pWindowHandle, SizeI ScreenSize)
{
	_WindowHandle = pWindowHandle;

	HRESULT hr;

	D3D_FEATURE_LEVEL FeatureLevels[] = {
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
	};

	hr = ::D3D11CreateDevice(
		0,
		D3D_DRIVER_TYPE_HARDWARE,
		0,
#if defined(ATS_DEBUG)
		D3D11_CREATE_DEVICE_SINGLETHREADED | D3D11_CREATE_DEVICE_DEBUG,
#else//defined(ATS_DEBUG)
		D3D11_CREATE_DEVICE_SINGLETHREADED,
#endif//defined(ATS_DEBUG)
		FeatureLevels,
		1,
		D3D11_SDK_VERSION,
		&_pDevice,
		nullptr,
		&_pDeviceContext);
	if FAILED(hr) return false;

	// デバイスからDXGIデバイスを取得
	hr = _pDevice->QueryInterface(__uuidof(IDXGIDevice1), (void**)&_pDXGIDevice);
	if FAILED(hr) return false;

	// DXGIデバイスからアダプターを取得
	hr = _pDXGIDevice->GetAdapter(&_pDXGIAdapter);
	if FAILED(hr) return false;

	// アダプターからファクトリーを取得
	hr = _pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&_pDXGIFactory);
	if FAILED(hr) return false;

	return CreateSwapChain(ScreenSize);
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
bool GraphicsDevice::CreateSwapChain(SizeI ScreenSize)
{
	_pDeviceContext->ClearState();
	_pDeviceContext->Flush();

	HWND hWnd = reinterpret_cast<HWND>(_WindowHandle);
	_BackBufferSize = ScreenSize;

	ATS_SAFE_RELEASE(_pBackBufferTexture);
	ATS_SAFE_RELEASE(_pBackBufferRenderTargetView);
	ATS_SAFE_RELEASE(_pSwapChain);

	HRESULT hr;

	// ファクトリーからスワップチェインを生成
	DXGI_SWAP_CHAIN_DESC SwapChainDesc;
	ZeroMemory(&SwapChainDesc, sizeof(SwapChainDesc));
	SwapChainDesc.BufferDesc.Width = _BackBufferSize.W;
	SwapChainDesc.BufferDesc.Height = _BackBufferSize.H;
	SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	SwapChainDesc.SampleDesc.Count = 1;
	SwapChainDesc.SampleDesc.Quality = 0;
	SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	SwapChainDesc.BufferCount = 2;
	SwapChainDesc.OutputWindow = hWnd;
	SwapChainDesc.Windowed = TRUE;
	SwapChainDesc.Flags = 0;
	hr = _pDXGIFactory->CreateSwapChain(_pDevice, &SwapChainDesc, &_pSwapChain);
	if FAILED(hr) return false;

	// スワップチェインからバックバッファを取得
	hr = _pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&_pBackBufferTexture);
	if FAILED(hr) return false;

	// バックバッファのRenderTargetViewを生成
	D3D11_RENDER_TARGET_VIEW_DESC ViewDesc;
	ZeroMemory(&ViewDesc, sizeof(ViewDesc));
	ViewDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	ViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	ViewDesc.Texture2D.MipSlice = 0;
	hr = _pDevice->CreateRenderTargetView(_pBackBufferTexture, &ViewDesc, &_pBackBufferRenderTargetView);
	if FAILED(hr) return false;

	// バックバッファクリア
	ClearBackBuffer(ColorF::BLACK);
	Present();

	return true;
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
SizeI GraphicsDevice::GetBackBufferSize()
{
	return _BackBufferSize;
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
void GraphicsDevice::Uninitialize()
{
	if (_pDeviceContext != nullptr)
	{
		_pDeviceContext->ClearState();
		_pDeviceContext->Flush();
	}

	ATS_SAFE_RELEASE(_pBackBufferRenderTargetView);
	ATS_SAFE_RELEASE(_pBackBufferTexture);
	ATS_SAFE_RELEASE(_pSwapChain);
	ATS_SAFE_RELEASE(_pDeviceContext);
	ATS_SAFE_RELEASE(_pDXGIFactory);
	ATS_SAFE_RELEASE(_pDXGIAdapter);
	ATS_SAFE_RELEASE(_pDXGIDevice);
	ATS_SAFE_RELEASE(_pDevice);
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
void GraphicsDevice::ClearBackBuffer(const ColorF& Color)
{
	_pDeviceContext->ClearRenderTargetView(_pBackBufferRenderTargetView, reinterpret_cast<const float_t*>(&Color));
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
void GraphicsDevice::Present()
{
	_pSwapChain->Present(0, 0);
	_pDeviceContext->ClearState();

	std::array<ID3D11RenderTargetView*, D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT> RenderTargetViews = {
		_pBackBufferRenderTargetView,
	};
	std::array<D3D11_VIEWPORT, D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT> Viewports = {
		{ 0.0f, 0.0f, static_cast<float_t>(_BackBufferSize.W), static_cast<float_t>(_BackBufferSize.H), 0.0f, 1.0f },
	};
	std::array<D3D11_RECT, D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT> SetScissorRects = {
		{ 0, 0, _BackBufferSize.W, _BackBufferSize.H },
	};
	
	_pDeviceContext->OMSetRenderTargets(D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT, RenderTargetViews.data(), nullptr);
	_pDeviceContext->RSSetViewports(D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT, Viewports.data());
	_pDeviceContext->RSSetScissorRects(D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT, SetScissorRects.data());
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
}
}
