//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#include "Artemis.Local.hpp"

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
static struct Global
{
	IDXGIDevice1* pDXGIDevice;
	IDXGIAdapter* pDXGIAdapter;
	IDXGIFactory* pDXGIFactory;
	ID3D11Device* pDevice;
	ID3D11DeviceContext* pDeviceContext;
	IDXGISwapChain* pSwapChain;
	ID3D11Texture2D* pRenderTargetTexutre;
	ID3D11RenderTargetView* pRenderTargetView;
}
_Global;

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
bool Initialize(void* pWindowHandle, SizeI ScreenSize)
{
	HWND hWnd = reinterpret_cast<HWND>(pWindowHandle);

	HRESULT hr;

	D3D_FEATURE_LEVEL FeatureLevels[] = {
		D3D_FEATURE_LEVEL_11_0,
	};

	hr = ::D3D11CreateDevice(
			0,
			D3D_DRIVER_TYPE_HARDWARE,
			0,
#if defined(ATS_DEBUG)
			D3D11_CREATE_DEVICE_DEBUG,
#else//defined(ATS_DEBUG)
			0,
#endif//defined(ATS_DEBUG)
			FeatureLevels,
			1,
			D3D11_SDK_VERSION,
			&_Global.pDevice,
			nullptr,
			&_Global.pDeviceContext);
	if FAILED(hr) return false;

	// デバイスからDXGIデバイスを取得
	hr = _Global.pDevice->QueryInterface(__uuidof(IDXGIDevice1), (void**)&_Global.pDXGIDevice);
	if FAILED(hr) return false;

	// DXGIデバイスからアダプターを取得
	hr = _Global.pDXGIDevice->GetAdapter(&_Global.pDXGIAdapter);
	if FAILED(hr) return false;

	// アダプターからファクトリーを取得
	hr = _Global.pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&_Global.pDXGIFactory);
	if FAILED(hr) return false;

	// ファクトリーからスワップチェインを生成
	DXGI_SWAP_CHAIN_DESC SwapChainDesc;
	ZeroMemory(&SwapChainDesc, sizeof(SwapChainDesc));
	SwapChainDesc.BufferDesc.Width = ScreenSize.W;
	SwapChainDesc.BufferDesc.Height = ScreenSize.H;
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
	hr = _Global.pDXGIFactory->CreateSwapChain(_Global.pDevice, &SwapChainDesc, &_Global.pSwapChain);
	if FAILED(hr) return false;

	// スワップチェインからバックバッファを取得
	hr = _Global.pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&_Global.pRenderTargetTexutre);
	if FAILED(hr) return false;

	// バックバッファのRenderTargetViewを生成
	D3D11_RENDER_TARGET_VIEW_DESC ViewDesc;
	ZeroMemory(&ViewDesc, sizeof(ViewDesc));
	ViewDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	ViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	ViewDesc.Texture2D.MipSlice = 0;
	hr = _Global.pDevice->CreateRenderTargetView(_Global.pRenderTargetTexutre, &ViewDesc, &_Global.pRenderTargetView);
	if FAILED(hr) return false;

	return true;
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
void Uninitialize()
{
	if (_Global.pDeviceContext != nullptr)
	{
		_Global.pDeviceContext->ClearState();
		_Global.pDeviceContext->Flush();
	}

	SAFE_RELEASE(_Global.pRenderTargetView);
	SAFE_RELEASE(_Global.pRenderTargetTexutre);
	SAFE_RELEASE(_Global.pSwapChain);
	SAFE_RELEASE(_Global.pDeviceContext);
	SAFE_RELEASE(_Global.pDXGIFactory);
	SAFE_RELEASE(_Global.pDXGIAdapter);
	SAFE_RELEASE(_Global.pDXGIDevice);
	SAFE_RELEASE(_Global.pDevice);
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
void Clear()
{
	float ClearColor[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	_Global.pDeviceContext->ClearRenderTargetView(_Global.pRenderTargetView, ClearColor);

	_Global.pDeviceContext->ClearState();
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
void Present()
{
	_Global.pSwapChain->Present(0, 0);
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
}
}
