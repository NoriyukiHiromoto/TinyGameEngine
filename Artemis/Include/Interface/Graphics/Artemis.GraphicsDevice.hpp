#pragma once

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#include "Artemis.GraphicsTypes.hpp"
#include "../Artemis.Interface.hpp"
#include "Artemis.Buffer.hpp"

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
class IGraphicsDevice
{
protected:
	IGraphicsDevice() { }
	virtual ~IGraphicsDevice() { }

public:
	virtual SizeI GetBackBufferSize() = 0;

	virtual IBuffer* CreateConstantBuffer(uint32_t BufferBytes) = 0;
	virtual IBuffer* CreateVertexBuffer(uint32_t BufferBytes) = 0;
	virtual IBuffer* CreateIndexBuffer(uint32_t BufferBytes) = 0;

	virtual IShader* CreateShader(const VertexInputLayoutData Layouts[], uint32_t LayoutCount, IShaderBinary* pVS, IShaderBinary* pPS) = 0;
	virtual IShader* CreateShader(const VertexInputLayoutData Layouts[], uint32_t LayoutCount, const void* pVS, const uint32_t VSSize, const void* pPS, const uint32_t PSSize) = 0;

	virtual void* Map(IBuffer* pBuffer) = 0;
	virtual void Unmap(IBuffer* pBuffer) = 0;

	virtual void SetConstantBuffer(eShaderType ShaderType, uint32_t Slot, IBuffer* pBuffer) = 0;
	virtual void SetVertexBuffer(uint32_t Slot, IBuffer* pBuffer, uint32_t Stride, uint32_t Offset) = 0;
	virtual void SetIndexBuffer(IBuffer* pBuffer, eIndexType IndexType, uint32_t Offset) = 0;

	virtual void SetRasterizerState(RasterizerState State) = 0;
	virtual void SetDepthStencilState(DepthStencilState State) = 0;
	virtual void SetBlendState(BlendState State) = 0;

	virtual void SetShader(IShader* pShader) = 0;

	virtual void SetPrimitiveTopology(ePrimitiveTopology Topology) = 0;
	virtual void Draw(uint32_t VertexCount, uint32_t InstanceCount, uint32_t StartVertexLocation, uint32_t StartInstanceLocation) = 0;
	virtual void DrawIndexed(uint32_t DrawIndexCount, uint32_t InstanceCount, uint32_t StartIndexLocation, uint32_t BaseVertexLocation, uint32_t StartInstanceLocation) = 0;
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
}
}
