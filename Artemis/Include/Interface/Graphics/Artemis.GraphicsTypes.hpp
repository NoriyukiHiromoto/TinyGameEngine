#pragma once

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#include "../../Artemis.Types.hpp"

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
enum class eBufferLocation : uint32_t
{
	Host,
	Device,

	OfMax,
};

enum class eBufferType : uint32_t
{
	Constant,
	Vertex,
	Index,

	OfMax,
};

enum class eIndexType : uint32_t
{
	UShort,
	UInt,

	OfMax,
};

enum class eShaderType : uint32_t
{
	Vertex,
	Pixel,
	Compute,

	OfMax,
};

enum class eBlendType : uint32_t
{
	Zero,
	One,
	SrcColor,
	InvSrcColor,
	SrcAlpha,
	InvSrcAlpha,
	DstColor,
	InvDstColor,
	DstAlpha,
	InvDstAlpha,

	OfMax,
};

enum class eBlendOperationType : uint32_t
{
	Add,
	Substract,
	RevSubstract,
	Min,
	Max,

	OfMax,
};

enum class eTextureFilter : uint32_t
{
	Point,
	Linear,
	Anisotropic,

	OfMax,
};

enum class eTextureMipFilter : uint32_t
{
	None,
	Point,
	Linear,

	OfMax,
};

enum class eTextureAddress : uint32_t
{
	Clamp,
	Wrap,
	Mirror,

	OfMax,
};

enum class eDepthWrite : uint32_t
{
	Disable,
	Enable,

	OfMax,
};

enum class eDepthTestFunction : uint32_t
{
	Never,
	Less,
	Equal,
	LessEqual,
	Greater,
	NotEqual,
	GreaterEqual,
	Always,

	OfMax,
};

enum class eFaceCullMode : uint32_t
{
	None,
	Front,
	Back,

	OfMax,
};

enum class eScissorTest : uint32_t
{
	Disable,
	Enable,

	OfMax,
};

enum class ePrimitiveTopology : uint32_t
{
	PointList,
	LineList,
	LineStrip,
	TriangleList,
	TriangleStrip,

	OfMax,
};

enum class eVertexInputLayoutSemanticType : uint32_t
{
	Position,
	Normal,
	Tangent,
	Color,
	Texcoord,

	OfMax,
};

enum class eVertexInputLayoutFormatType : uint32_t
{
	Float1,
	Float2,
	Float3,
	Float4,
	Half2,
	Half4,
	Sint16x2,
	Sint16x4,
	Sint16Normalx2,
	Sint16Normalx4,
	Uint16x2,
	Uint16x4,
	Uint16Normalx2,
	Uint16Normalx4,
	Uint8x4,
	Sint8x4,
	Uint8Normalx4,
	Sint8Normalx4,

	OfMax,
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
static constexpr uint32_t CONSTANT_BUFFER_SLOT_MAX = 8;
static constexpr uint32_t VERTEX_BUFFER_SLOT_MAX = 4;
static constexpr uint32_t RENDER_TARGET_SLOT_MAX = 8;

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
struct VertexInputLayoutData
{
	int32_t							StreamNo;
	eVertexInputLayoutSemanticType	SemanticType;
	int32_t							SemanticIndex;
	eVertexInputLayoutFormatType	FormatType;
	int32_t							DataOffset;
};

union RasterizerState
{
	struct {
		eFaceCullMode FaceCullMode : 2;
		eScissorTest ScissorTest : 1;
	};
	uint32_t State;

	RasterizerState()
		: FaceCullMode(eFaceCullMode::None)
		, ScissorTest(eScissorTest::Disable)
	{
	}
};
static_assert(sizeof(RasterizerState) == sizeof(uint32_t), "invalid class size [RasterizerState]");

union DepthStencilState
{
	struct {
		eDepthWrite DepthWrite : 1;
		eDepthTestFunction DepthTestFunction : 3;
	};
	uint32_t State;

	DepthStencilState()
		: DepthWrite(eDepthWrite::Disable)
		, DepthTestFunction(eDepthTestFunction::Always)
	{
	}
};
static_assert(sizeof(DepthStencilState) == sizeof(uint32_t), "invalid class size [DepthStencilState]");

union BlendState
{
	struct {
		uint32_t IsBlendEnable : 1;
		uint32_t IsColorRWrite : 1;
		uint32_t IsColorGWrite : 1;
		uint32_t IsColorBWrite : 1;
		uint32_t IsAlphaWrite : 1;
		eBlendOperationType BlendOpAlpha : 3;
		eBlendType DestBlendAlpha : 4;
		eBlendType SrcBlendAlpha : 4;
		eBlendOperationType BlendOp : 3;
		eBlendType DestBlend : 4;
		eBlendType SrcBlend : 4;
	};
	uint32_t State;

	BlendState()
		: IsBlendEnable(0)
		, IsColorRWrite(1)
		, IsColorGWrite(1)
		, IsColorBWrite(1)
		, IsAlphaWrite(1)
		, BlendOpAlpha(eBlendOperationType::Add)
		, DestBlendAlpha(eBlendType::Zero)
		, SrcBlendAlpha(eBlendType::One)
		, BlendOp(eBlendOperationType::Add)
		, DestBlend(eBlendType::Zero)
		, SrcBlend(eBlendType::One)
	{
	}
};
static_assert(sizeof(BlendState) == sizeof(uint32_t), "invalid class size [BlendState]");

union SamplerState
{
	struct {
		eTextureFilter Filter : 2;
		eTextureMipFilter MipFilter : 2;
		eTextureAddress AddressU : 2;
		eTextureAddress AddressV : 2;
	};
	uint32_t State;

	SamplerState()
		: Filter(eTextureFilter::Point)
		, MipFilter(eTextureMipFilter::None)
		, AddressU(eTextureAddress::Clamp)
		, AddressV(eTextureAddress::Clamp)
	{
	}
};
static_assert(sizeof(SamplerState) == sizeof(uint32_t), "invalid class size [SamplerState]");

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
}
}
