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

	struct {
		struct ConstantBufferData {
			std::array<ID3D11Buffer*, CONSTANT_BUFFER_SLOT_MAX> pBuffer;
		} _VSConstantBuffer, _PSConstantBuffer, _CSConstantBuffer;

		struct VertexBufferData {
			std::array<ID3D11Buffer*, VERTEX_BUFFER_SLOT_MAX> pBuffer;
			std::array<UINT, VERTEX_BUFFER_SLOT_MAX> Stride;
			std::array<UINT, VERTEX_BUFFER_SLOT_MAX> Offset;
		} _VertexBuffer;

		struct IndexBufferData {
			ID3D11Buffer* pBuffer;
			eIndexType IndexType;
			uint32_t Offset;
		} _IndexBuffer;

		ID3D11InputLayout* _pInputLayout;
		ID3D11VertexShader* _pVertexShader;
		ID3D11PixelShader* _pPixelShader;
		ePrimitiveTopology _PrimitiveTopology;
		RasterizerState _RasterizerState;
		DepthStencilState _DepthStencilState;
		BlendState _BlendState;
	} _CurrentData;

	std::map <uint32_t, ID3D11BlendState*> _BlendStateMap;
	std::map<uint32_t, ID3D11DepthStencilState*> _DepthStencilStateMap;
	std::map<uint32_t, ID3D11RasterizerState*> _RasterizerStateMap;

private:
	bool SubmitRenderData(bool UseIndexBuffer);
	ID3D11BlendState* GetID3D11BlendState(BlendState State);
	ID3D11DepthStencilState* GetID3D11DepthStencilState(DepthStencilState State);
	ID3D11RasterizerState* GetID3D11RasterizerState(RasterizerState State);

public:
	bool Initialize(void* pWindowHandle, SizeI ScreenSize);
	void Uninitialize();
	bool CreateSwapChain(SizeI ScreenSize);
	void ClearBackBuffer(const ColorF& Color);
	void Present();

public:
	virtual SizeI GetBackBufferSize() override;

	virtual IBuffer* CreateConstantBuffer(uint32_t BufferBytes) override;
	virtual IBuffer* CreateVertexBuffer(uint32_t BufferBytes) override;
	virtual IBuffer* CreateIndexBuffer(uint32_t BufferBytes) override;

	virtual IShader* CreateShader(const VertexInputLayoutData Layouts[], uint32_t LayoutCount, IShaderBinary* pVS, IShaderBinary* pPS) override;
	virtual IShader* CreateShader(const VertexInputLayoutData Layouts[], uint32_t LayoutCount, const void* pVS, const uint32_t VSSize, const void* pPS, const uint32_t PSSize) override;

	virtual void* Map(IBuffer* pBuffer) override;
	virtual void Unmap(IBuffer* pBuffer) override;

	virtual void SetConstantBuffer(eShaderType ShaderType, uint32_t Slot, IBuffer* pBuffer) override;
	virtual void SetVertexBuffer(uint32_t Slot, IBuffer* pBuffer, uint32_t Stride, uint32_t Offset) override;
	virtual void SetIndexBuffer(IBuffer* pBuffer, eIndexType IndexType, uint32_t Offset) override;

	virtual void SetRasterizerState(RasterizerState State) override;
	virtual void SetDepthStencilState(DepthStencilState State) override;
	virtual void SetBlendState(BlendState State) override;

	virtual void SetShader(IShader* pShader) override;

	virtual void SetPrimitiveTopology(ePrimitiveTopology Topology) override;
	virtual void Draw(uint32_t VertexCount, uint32_t InstanceCount, uint32_t StartVertexLocation, uint32_t StartInstanceLocation) override;
	virtual void DrawIndexed(uint32_t DrawIndexCount, uint32_t InstanceCount, uint32_t StartIndexLocation, uint32_t BaseVertexLocation, uint32_t StartInstanceLocation) override;
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
}
}
