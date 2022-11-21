
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
	for (auto&& state : _BlendStateMap)
	{
		ATS_SAFE_RELEASE(state.second);
	}
	_BlendStateMap.clear();

	for (auto&& state : _DepthStencilStateMap)
	{
		ATS_SAFE_RELEASE(state.second);
	}
	_DepthStencilStateMap.clear();

	for (auto&& state : _RasterizerStateMap)
	{
		ATS_SAFE_RELEASE(state.second);
	}
	_RasterizerStateMap.clear();

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
IBuffer* GraphicsDevice::CreateConstantBuffer(uint32_t BufferBytes)
{
	ATS_ASSERT(BufferBytes > 0, "バッファサイズが0Byteです");
	ATS_ASSERT((BufferBytes & 0xF) == 0, "バッファサイズが16Byteアライメントされていません");

	D3D11_BUFFER_DESC BufferDesc;
	BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	BufferDesc.ByteWidth = BufferBytes;
	BufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	BufferDesc.MiscFlags = 0;

	ID3D11Buffer* pBuffer;
	HRESULT hr = _pDevice->CreateBuffer(&BufferDesc, nullptr, &pBuffer);

	return SUCCEEDED(hr) ? ATS_NEW Buffer(eBufferType::Constant, pBuffer) : nullptr;
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
IBuffer* GraphicsDevice::CreateVertexBuffer(uint32_t BufferBytes)
{
	ATS_ASSERT(BufferBytes > 0, "バッファサイズが0Byteです");

	D3D11_BUFFER_DESC BufferDesc;
	BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	BufferDesc.ByteWidth = BufferBytes;
	BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	BufferDesc.MiscFlags = 0;

	ID3D11Buffer* pBuffer;
	HRESULT hr = _pDevice->CreateBuffer(&BufferDesc, nullptr, &pBuffer);

	return SUCCEEDED(hr) ? ATS_NEW Buffer(eBufferType::Vertex, pBuffer) : nullptr;
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
IBuffer* GraphicsDevice::CreateIndexBuffer(uint32_t BufferBytes)
{
	ATS_ASSERT(BufferBytes > 0, "バッファサイズが0Byteです");

	D3D11_BUFFER_DESC BufferDesc;
	BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	BufferDesc.ByteWidth = BufferBytes;
	BufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	BufferDesc.MiscFlags = 0;

	ID3D11Buffer* pBuffer;
	HRESULT hr = _pDevice->CreateBuffer(&BufferDesc, nullptr, &pBuffer);

	return SUCCEEDED(hr) ? ATS_NEW Buffer(eBufferType::Index, pBuffer) : nullptr;
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
IShader* GraphicsDevice::CreateShader(const VertexInputLayoutData Layouts[], uint32_t LayoutCount, IShaderBinary* pVS, IShaderBinary* pPS)
{
	return CreateShader(
		Layouts, LayoutCount,
		pVS->GetCodePointer(), pVS->GetCodeSize(),
		pPS->GetCodePointer(), pPS->GetCodeSize());
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
IShader* GraphicsDevice::CreateShader(const VertexInputLayoutData Layouts[], uint32_t LayoutCount, const void* pVS, const uint32_t VSSize, const void* pPS, const uint32_t PSSize)
{
	auto Convert = [](D3D11_INPUT_ELEMENT_DESC & Dst, const VertexInputLayoutData & Src, uint32_t DataOffset)
	{
		static constexpr std::array<const char*, (int32_t)eVertexInputLayoutSemanticType::OfMax> SemanticNameTbl = {
			"Position",						// eVertexInputLayoutSemanticType::Position,
			"Normal",						// eVertexInputLayoutSemanticType::Normal,
			"Tangent",						// eVertexInputLayoutSemanticType::Tangent,
			"Color",						// eVertexInputLayoutSemanticType::Color,
			"Texcood",						// eVertexInputLayoutSemanticType::Texcoord,
		};
		static constexpr std::array<DXGI_FORMAT, (int32_t)eVertexInputLayoutFormatType::OfMax> FormatTbl = {
			DXGI_FORMAT_R32_FLOAT,			// eVertexInputLayoutFormatType::Float1,
			DXGI_FORMAT_R32G32_FLOAT,		// eVertexInputLayoutFormatType::Float2,
			DXGI_FORMAT_R32G32B32_FLOAT,	// eVertexInputLayoutFormatType::Float3,
			DXGI_FORMAT_R32G32B32A32_FLOAT,	// eVertexInputLayoutFormatType::Float4,
			DXGI_FORMAT_R16G16_FLOAT,		// eVertexInputLayoutFormatType::Half2,
			DXGI_FORMAT_R16G16B16A16_FLOAT,	// eVertexInputLayoutFormatType::Half4,
			DXGI_FORMAT_R16G16_SINT,		// eVertexInputLayoutFormatType::Sint16x2,
			DXGI_FORMAT_R16G16B16A16_SINT,	// eVertexInputLayoutFormatType::Sint16x4,
			DXGI_FORMAT_R16G16_SNORM,		// eVertexInputLayoutFormatType::Sint16Normalx2,
			DXGI_FORMAT_R16G16B16A16_SNORM,	// eVertexInputLayoutFormatType::Sint16Normalx4,
			DXGI_FORMAT_R16G16_UINT,		// eVertexInputLayoutFormatType::Uint16x2,
			DXGI_FORMAT_R16G16B16A16_UINT,	// eVertexInputLayoutFormatType::Uint16x4,
			DXGI_FORMAT_R16G16_UNORM,		// eVertexInputLayoutFormatType::Uint16Normalx2,
			DXGI_FORMAT_R16G16B16A16_UNORM,	// eVertexInputLayoutFormatType::Uint16Normalx4,
			DXGI_FORMAT_R8G8B8A8_UINT,		// eVertexInputLayoutFormatType::Uint8x4,
			DXGI_FORMAT_R8G8B8A8_SINT,		// eVertexInputLayoutFormatType::Sint8x4,
			DXGI_FORMAT_R8G8B8A8_UNORM,		// eVertexInputLayoutFormatType::Uint8Normalx4,
			DXGI_FORMAT_R8G8B8A8_SNORM,		// eVertexInputLayoutFormatType::Sint8Normalx4,
		};
		static constexpr std::array<uint32_t, (int32_t)eVertexInputLayoutFormatType::OfMax> SizeTbl = {
			sizeof(float_t) * 1,			// eVertexInputLayoutFormatType::Float1,
			sizeof(float_t) * 2,			// eVertexInputLayoutFormatType::Float2,
			sizeof(float_t) * 3,			// eVertexInputLayoutFormatType::Float3,
			sizeof(float_t) * 4,			// eVertexInputLayoutFormatType::Float4,
			sizeof(int16_t) * 2,			// eVertexInputLayoutFormatType::Half2,
			sizeof(int16_t) * 4,			// eVertexInputLayoutFormatType::Half4,
			sizeof(int16_t) * 2,			// eVertexInputLayoutFormatType::Sint16x2,
			sizeof(int16_t) * 4,			// eVertexInputLayoutFormatType::Sint16x4,
			sizeof(int16_t) * 2,			// eVertexInputLayoutFormatType::Sint16Normalx2,
			sizeof(int16_t) * 4,			// eVertexInputLayoutFormatType::Sint16Normalx4,
			sizeof(int16_t) * 2,			// eVertexInputLayoutFormatType::Sint16x2,
			sizeof(int16_t) * 4,			// eVertexInputLayoutFormatType::Sint16x4,
			sizeof(int16_t) * 2,			// eVertexInputLayoutFormatType::Sint16Normalx2,
			sizeof(int16_t) * 4,			// eVertexInputLayoutFormatType::Sint16Normalx4,
			sizeof(uint8_t) * 4,			// eVertexInputLayoutFormatType::Uint8x4,
			sizeof(uint8_t) * 4,			// eVertexInputLayoutFormatType::Sint8x4,
			sizeof(uint8_t) * 4,			// eVertexInputLayoutFormatType::Uint8Normalx4,
			sizeof(uint8_t) * 4,			// eVertexInputLayoutFormatType::Sint8Normalx4,
		};
		Dst.SemanticName = SemanticNameTbl[static_cast<std::underlying_type<eVertexInputLayoutSemanticType>::type>(Src.SemanticType)];
		Dst.SemanticIndex = Src.SemanticIndex;
		Dst.Format = FormatTbl[static_cast<std::underlying_type<eVertexInputLayoutFormatType>::type>(Src.FormatType)];
		Dst.InputSlot = Src.StreamNo;
		Dst.AlignedByteOffset = Src.DataOffset == -1 ? DataOffset : Src.DataOffset;
		Dst.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		Dst.InstanceDataStepRate = 0;

		return Dst.AlignedByteOffset + SizeTbl[static_cast<std::underlying_type<eVertexInputLayoutFormatType>::type>(Src.FormatType)];
	};

	ID3D11InputLayout* pInputLayout = nullptr;
	ID3D11VertexShader* pVertexShader = nullptr;
	ID3D11PixelShader* pPixelShader = nullptr;

	HRESULT hr;

	ATS_ASSERT(LayoutCount <= D3D11_IA_VERTEX_INPUT_STRUCTURE_ELEMENT_COUNT, "LayoutCount is too many");
	uint32_t DataOffset = 0;
	D3D11_INPUT_ELEMENT_DESC DescTbl[D3D11_IA_VERTEX_INPUT_STRUCTURE_ELEMENT_COUNT] = { {} };
	for (uint32_t i = 0; i < LayoutCount; ++i)
	{
		DataOffset = Convert(DescTbl[i], Layouts[i], DataOffset);
	}

	hr = _pDevice->CreateInputLayout(DescTbl, LayoutCount, pVS, VSSize, &pInputLayout);
	if FAILED(hr) goto EXIT;
	hr = _pDevice->CreateVertexShader(pVS, VSSize, nullptr, &pVertexShader);
	if FAILED(hr) goto EXIT;
	hr = _pDevice->CreatePixelShader(pPS, PSSize, nullptr, &pPixelShader);
	if FAILED(hr) goto EXIT;

	return ATS_NEW Shader(pInputLayout, pVertexShader, pPixelShader);

EXIT:
	ATS_SAFE_RELEASE(pInputLayout);
	ATS_SAFE_RELEASE(pVertexShader);
	ATS_SAFE_RELEASE(pPixelShader);

	return nullptr;
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
void* GraphicsDevice::Map(IBuffer* pBuffer)
{
	auto pBufferImpl = reinterpret_cast<Buffer*>(pBuffer);
	if (pBufferImpl == nullptr) return nullptr;

	D3D11_MAPPED_SUBRESOURCE MappedResource;
	HRESULT hr = _pDeviceContext->Map(pBufferImpl->GetNativePointer(), 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedResource);
	return SUCCEEDED(hr) ? MappedResource.pData : nullptr;
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
void GraphicsDevice::Unmap(IBuffer* pBuffer)
{
	auto pBufferImpl = reinterpret_cast<Buffer*>(pBuffer);
	if (pBufferImpl == nullptr) return;

	_pDeviceContext->Unmap(pBufferImpl->GetNativePointer(), 0);
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
void GraphicsDevice::SetConstantBuffer(eShaderType ShaderType, uint32_t Slot, IBuffer* pBuffer)
{
	auto pBufferImpl = reinterpret_cast<Buffer*>(pBuffer);
	ATS_ASSERT((pBufferImpl == nullptr) || (pBufferImpl->BufferType() == eBufferType::Constant), "Invalid BufferType");

	ID3D11Buffer* pID3D11Buffer = pBufferImpl == nullptr ? nullptr : pBufferImpl->GetNativePointer();
	switch (ShaderType)
	{
	case eShaderType::Vertex:
		_CurrentData._VSConstantBuffer.pBuffer[Slot] = pID3D11Buffer;
		break;
	case eShaderType::Pixel:
		_CurrentData._PSConstantBuffer.pBuffer[Slot] = pID3D11Buffer;
		break;
	case eShaderType::Compute:
		_CurrentData._CSConstantBuffer.pBuffer[Slot] = pID3D11Buffer;
		break;
	}
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
void GraphicsDevice::SetVertexBuffer(uint32_t Slot, IBuffer* pBuffer, uint32_t Stride, uint32_t Offset)
{
	auto pBufferImpl = reinterpret_cast<Buffer*>(pBuffer);
	ATS_ASSERT((pBufferImpl == nullptr) || (pBufferImpl->BufferType() == eBufferType::Vertex), "Invalid BufferType");

	_CurrentData._VertexBuffer.pBuffer[Slot] = pBufferImpl == nullptr ? nullptr : pBufferImpl->GetNativePointer();
	_CurrentData._VertexBuffer.Offset[Slot] = Offset;
	_CurrentData._VertexBuffer.Stride[Slot] = Stride;
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
void GraphicsDevice::SetIndexBuffer(IBuffer* pBuffer, eIndexType IndexType, uint32_t Offset)
{
	auto pBufferImpl = reinterpret_cast<Buffer*>(pBuffer);
	ATS_ASSERT((pBufferImpl == nullptr) || (pBufferImpl->BufferType() == eBufferType::Index), "Invalid BufferType");

	_CurrentData._IndexBuffer.pBuffer = pBufferImpl == nullptr ? nullptr : pBufferImpl->GetNativePointer();
	_CurrentData._IndexBuffer.IndexType = IndexType;
	_CurrentData._IndexBuffer.Offset = Offset;
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
void GraphicsDevice::SetRasterizerState(RasterizerState State)
{
	_CurrentData._RasterizerState = State;
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
void GraphicsDevice::SetDepthStencilState(DepthStencilState State)
{
	_CurrentData._DepthStencilState = State;
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
void GraphicsDevice::SetBlendState(BlendState State)
{
	_CurrentData._BlendState = State;
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
void GraphicsDevice::SetShader(IShader* pShader)
{
	auto pShaderImpl = reinterpret_cast<Shader*>(pShader);
	if (pShaderImpl == nullptr)
	{
		_CurrentData._pInputLayout = nullptr;
		_CurrentData._pVertexShader = nullptr;
		_CurrentData._pPixelShader = nullptr;
	}
	else
	{
		_CurrentData._pInputLayout = pShaderImpl->GetInputLayout();
		_CurrentData._pVertexShader = pShaderImpl->GetVertexShader();
		_CurrentData._pPixelShader = pShaderImpl->GetPixelShader();
	}
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
void GraphicsDevice::SetPrimitiveTopology(ePrimitiveTopology Topology)
{
	_CurrentData._PrimitiveTopology = Topology;
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
void GraphicsDevice::Draw(uint32_t VertexCount, uint32_t InstanceCount, uint32_t StartVertexLocation, uint32_t StartInstanceLocation)
{
	if (InstanceCount == 0) return;
	if (VertexCount == 0) return;

	SubmitRenderData(false);

	_pDeviceContext->DrawInstanced(VertexCount, InstanceCount, StartVertexLocation, StartInstanceLocation);
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
void GraphicsDevice::DrawIndexed(uint32_t DrawIndexCount, uint32_t InstanceCount, uint32_t StartIndexLocation, uint32_t BaseVertexLocation, uint32_t StartInstanceLocation)
{
	if (InstanceCount == 0) return;
	if (DrawIndexCount == 0) return;

	SubmitRenderData(true);

	_pDeviceContext->DrawIndexedInstanced(DrawIndexCount, InstanceCount, StartIndexLocation, BaseVertexLocation, StartInstanceLocation);
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
bool GraphicsDevice::SubmitRenderData(bool UseIndexBuffer)
{
	{
		static constexpr FLOAT BlendFactor[] = { 0.0f ,0.0f ,0.0f ,0.0f };
		_pDeviceContext->OMSetBlendState(GetID3D11BlendState(_CurrentData._BlendState), BlendFactor, 0xFFFFFFFF);
		_pDeviceContext->OMSetDepthStencilState(GetID3D11DepthStencilState(_CurrentData._DepthStencilState), 0x00);
		_pDeviceContext->RSSetState(GetID3D11RasterizerState(_CurrentData._RasterizerState));
	}

	{
		_pDeviceContext->VSSetConstantBuffers(
			0, CONSTANT_BUFFER_SLOT_MAX,
			_CurrentData._VSConstantBuffer.pBuffer.data());

		_pDeviceContext->PSSetConstantBuffers(
			0, CONSTANT_BUFFER_SLOT_MAX,
			_CurrentData._PSConstantBuffer.pBuffer.data());
	}

	{
		_pDeviceContext->IASetVertexBuffers(
			0, VERTEX_BUFFER_SLOT_MAX,
			_CurrentData._VertexBuffer.pBuffer.data(),
			_CurrentData._VertexBuffer.Stride.data(),
			_CurrentData._VertexBuffer.Offset.data());
	}

	{
		if (_CurrentData._pInputLayout == nullptr)
		{
			ATS_MESSAGE("_CurrentData._pInputLayout is null.");
			return false;
		}

		_pDeviceContext->IASetInputLayout(_CurrentData._pInputLayout);
		_pDeviceContext->VSSetShader(_CurrentData._pVertexShader, nullptr, 0);
		_pDeviceContext->PSSetShader(_CurrentData._pPixelShader, nullptr, 0);
	}

	if (UseIndexBuffer)
	{
		if (_CurrentData._IndexBuffer.pBuffer == nullptr)
		{
			ATS_MESSAGE("_CurrentData._IndexBuffer.pBuffer is null.");
			return false;
		}

		static constexpr std::array<DXGI_FORMAT, 2> FormatTbl = {
			DXGI_FORMAT_R16_UINT,		// eIndexType::UShort
			DXGI_FORMAT_R32_UINT,		// eIndexType::UInt
		};
		const auto Format = static_cast<std::underlying_type<eIndexType>::type>(_CurrentData._IndexBuffer.IndexType);
		_pDeviceContext->IASetIndexBuffer(_CurrentData._IndexBuffer.pBuffer, FormatTbl[Format], _CurrentData._IndexBuffer.Offset);
	}

	{
		static constexpr std::array<D3D11_PRIMITIVE_TOPOLOGY, 5> TypeTbl = {
			D3D11_PRIMITIVE_TOPOLOGY_POINTLIST,			// ePrimitiveTopology::PointList
			D3D11_PRIMITIVE_TOPOLOGY_LINELIST,			// ePrimitiveTopology::LineList
			D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP,			// ePrimitiveTopology::LineStrip
			D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,		// ePrimitiveTopology::TriangleList
			D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,		// ePrimitiveTopology::TriangleStrip
		};
		const auto Type = static_cast<std::underlying_type<ePrimitiveTopology>::type>(_CurrentData._PrimitiveTopology);
		_pDeviceContext->IASetPrimitiveTopology(TypeTbl[Type]);
	}

	return true;
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
ID3D11BlendState* GraphicsDevice::GetID3D11BlendState(BlendState State)
{
	auto it = _BlendStateMap.find(State.State);
	if (it != _BlendStateMap.end())
	{
		return (*it).second;
	}

	ID3D11BlendState* pState = nullptr;

	static constexpr std::array<D3D11_BLEND, 10> BlendTbl = {
		D3D11_BLEND_ZERO,				// eBlendType::Zero
		D3D11_BLEND_ONE,				// eBlendType::One
		D3D11_BLEND_SRC_COLOR,			// eBlendType::SrcColor
		D3D11_BLEND_INV_SRC_COLOR,		// eBlendType::InvSrcColor
		D3D11_BLEND_SRC_ALPHA,			// eBlendType::SrcAlpha
		D3D11_BLEND_INV_SRC_ALPHA,		// eBlendType::InvSrcAlpha
		D3D11_BLEND_DEST_COLOR,			// eBlendType::DstColor
		D3D11_BLEND_INV_DEST_COLOR,		// eBlendType::InvDstColor
		D3D11_BLEND_DEST_ALPHA,			// eBlendType::DstAlpha
		D3D11_BLEND_INV_DEST_ALPHA,		// eBlendType::InvDstAlpha
	};
	static constexpr std::array<D3D11_BLEND_OP, 5> BlendOpTbl = {
		D3D11_BLEND_OP_ADD,				// eBlendOperationType::Add
		D3D11_BLEND_OP_SUBTRACT,		// eBlendOperationType::Substract
		D3D11_BLEND_OP_REV_SUBTRACT,	// eBlendOperationType::RevSubstract
		D3D11_BLEND_OP_MIN,				// eBlendOperationType::Min
		D3D11_BLEND_OP_MAX,				// eBlendOperationType::Max
	};

	D3D11_BLEND_DESC Desc;
	Desc.AlphaToCoverageEnable = FALSE;
	Desc.IndependentBlendEnable = FALSE;
	for (uint32_t i = 0; i < D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT; ++i)
	{
		Desc.RenderTarget[i].BlendEnable = State.IsBlendEnable;
		Desc.RenderTarget[i].SrcBlend = BlendTbl[static_cast<std::underlying_type<eBlendType>::type>(State.SrcBlend)];
		Desc.RenderTarget[i].DestBlend = BlendTbl[static_cast<std::underlying_type<eBlendType>::type>(State.DestBlend)];
		Desc.RenderTarget[i].BlendOp = BlendOpTbl[static_cast<std::underlying_type<eBlendOperationType>::type>(State.BlendOp)];
		Desc.RenderTarget[i].SrcBlendAlpha = BlendTbl[static_cast<std::underlying_type<eBlendType>::type>(State.SrcBlendAlpha)];
		Desc.RenderTarget[i].DestBlendAlpha = BlendTbl[static_cast<std::underlying_type<eBlendType>::type>(State.DestBlendAlpha)];
		Desc.RenderTarget[i].BlendOpAlpha = BlendOpTbl[static_cast<std::underlying_type<eBlendOperationType>::type>(State.BlendOpAlpha)];
		Desc.RenderTarget[i].RenderTargetWriteMask =
			(State.IsColorRWrite ? D3D11_COLOR_WRITE_ENABLE_RED   : 0) |
			(State.IsColorGWrite ? D3D11_COLOR_WRITE_ENABLE_GREEN : 0) |
			(State.IsColorBWrite ? D3D11_COLOR_WRITE_ENABLE_BLUE  : 0) |
			(State.IsAlphaWrite  ? D3D11_COLOR_WRITE_ENABLE_ALPHA : 0);
	}

	HRESULT hr = _pDevice->CreateBlendState(&Desc, &pState);
	ATS_ASSERT(SUCCEEDED(hr), "Failed. CreateBlendState");

	_BlendStateMap.insert(std::make_pair(State.State, pState));

	return pState;
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
ID3D11DepthStencilState* GraphicsDevice::GetID3D11DepthStencilState(DepthStencilState State)
{
	auto it = _DepthStencilStateMap.find(State.State);
	if (it != _DepthStencilStateMap.end())
	{
		return (*it).second;
	}

	ID3D11DepthStencilState* pState = nullptr;

	static constexpr std::array<D3D11_DEPTH_WRITE_MASK, 2> DepthWriteTbl = {
		D3D11_DEPTH_WRITE_MASK_ZERO,		// eDepthWrite::Disable
		D3D11_DEPTH_WRITE_MASK_ALL,			// eDepthWrite::Enable
	};
	static constexpr std::array<D3D11_COMPARISON_FUNC, 8> DepthTestTbl = {
		D3D11_COMPARISON_NEVER,				// eDepthTestFunction::Never
		D3D11_COMPARISON_LESS,				// eDepthTestFunction::Less
		D3D11_COMPARISON_EQUAL,				// eDepthTestFunction::Equal
		D3D11_COMPARISON_LESS_EQUAL,		// eDepthTestFunction::LessEqual
		D3D11_COMPARISON_GREATER,			// eDepthTestFunction::Greater
		D3D11_COMPARISON_NOT_EQUAL,			// eDepthTestFunction::NotEqual
		D3D11_COMPARISON_GREATER_EQUAL,		// eDepthTestFunction::GreaterEqual
		D3D11_COMPARISON_ALWAYS,			// eDepthTestFunction::Always
	};

	D3D11_DEPTH_STENCIL_DESC Desc;
	Desc.DepthEnable = (State.DepthWrite != eDepthWrite::Disable) || (State.DepthTestFunction != eDepthTestFunction::Always);
	Desc.DepthWriteMask = DepthWriteTbl[static_cast<std::underlying_type<eDepthWrite>::type>(State.DepthWrite)];
	Desc.DepthFunc = DepthTestTbl[static_cast<std::underlying_type<eDepthTestFunction>::type>(State.DepthTestFunction)];
	Desc.StencilEnable = FALSE;
	Desc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
	Desc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;
	Desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	Desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	Desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	Desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	Desc.BackFace = Desc.FrontFace;

	HRESULT hr = _pDevice->CreateDepthStencilState(&Desc, &pState);
	ATS_ASSERT(SUCCEEDED(hr), "Failed. CreateDepthStencilState");

	_DepthStencilStateMap.insert(std::make_pair(State.State, pState));

	return pState;
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
ID3D11RasterizerState* GraphicsDevice::GetID3D11RasterizerState(RasterizerState State)
{
	auto it = _RasterizerStateMap.find(State.State);
	if (it != _RasterizerStateMap.end())
	{
		return (*it).second;
	}

	ID3D11RasterizerState* pState = nullptr;

	static constexpr std::array<D3D11_CULL_MODE, 3> CullModeTbl = {
		D3D11_CULL_NONE,		// eFaceCullMode::None
		D3D11_CULL_FRONT,		// eFaceCullMode::Front
		D3D11_CULL_BACK,		// eFaceCullMode::Back
	};
	static constexpr std::array<BOOL, 2> ScissorTestTbl = {
		FALSE,					// eScissorTest::Disable
		TRUE,					// eScissorTest::Enable
	};

	D3D11_RASTERIZER_DESC Desc;
	Desc.FillMode = D3D11_FILL_SOLID;
	Desc.CullMode = CullModeTbl[static_cast<std::underlying_type<eFaceCullMode>::type>(State.FaceCullMode)];
	Desc.FrontCounterClockwise = FALSE;
	Desc.DepthBias = 0;
	Desc.DepthBiasClamp = 0.0f;
	Desc.SlopeScaledDepthBias = 0.0f;
	Desc.DepthClipEnable = TRUE;
	Desc.ScissorEnable = ScissorTestTbl[static_cast<std::underlying_type<eScissorTest>::type>(State.ScissorTest)];
	Desc.MultisampleEnable = FALSE;
	Desc.AntialiasedLineEnable = FALSE;

	HRESULT hr = _pDevice->CreateRasterizerState(&Desc, &pState);
	ATS_ASSERT(SUCCEEDED(hr), "Failed. CreateRasterizerState");

	_RasterizerStateMap.insert(std::make_pair(State.State, pState));

	return pState;
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
}
}
