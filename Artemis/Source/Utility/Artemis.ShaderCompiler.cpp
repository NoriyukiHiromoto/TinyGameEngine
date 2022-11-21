//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#include <Utility/Artemis.ShaderCompiler.hpp>
#include <Graphics/Artemis.ShaderBinary.hpp>
#include "Artemis.Local.hpp"

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
namespace Artemis
{
namespace Utility
{

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
Graphics::IShaderBinary* ShaderCompiler::CompileVertexShader(const char* pShaderName, const char* pEntryPoint, const char* pShaderCode)
{
#if defined(ATS_DEBUG)
	constexpr uint32_t CompileFlag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else//defined(ATS_DEBUG)
	constexpr uint32_t CompileFlag = D3DCOMPILE_OPTIMIZATION_LEVEL2;
#endif//defined(ATS_DEBUG)

	Graphics::ShaderBinary* pShaderBinary = nullptr;

	ID3DBlob* pCode = nullptr;
	ID3DBlob* pError = nullptr;

	HRESULT hr = ::D3DCompile(
		pShaderCode,
		strlen(pShaderCode),
		pShaderName,
		nullptr,
		nullptr,
		pEntryPoint,
		"vs_5_0",
		CompileFlag,
		0,
		&pCode,
		&pError);
	if FAILED(hr)
	{
		ATS_MESSAGE(reinterpret_cast<const char*>(pError->GetBufferPointer()));
	}
	else
	{
		pShaderBinary = ATS_NEW Graphics::ShaderBinary(pCode->GetBufferPointer(), pCode->GetBufferSize());
	}

	ATS_SAFE_RELEASE(pCode);
	ATS_SAFE_RELEASE(pError);

	return pShaderBinary;
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
Graphics::IShaderBinary* ShaderCompiler::CompilePixelShader(const char* pShaderName, const char* pEntryPoint, const char* pShaderCode)
{
#if defined(ATS_DEBUG)
	constexpr uint32_t CompileFlag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else//defined(ATS_DEBUG)
	constexpr uint32_t CompileFlag = D3DCOMPILE_OPTIMIZATION_LEVEL2;
#endif//defined(ATS_DEBUG)

	Graphics::ShaderBinary* pShaderBinary = nullptr;

	ID3DBlob* pCode = nullptr;
	ID3DBlob* pError = nullptr;

	HRESULT hr = ::D3DCompile(
		pShaderCode,
		strlen(pShaderCode),
		pShaderName,
		nullptr,
		nullptr,
		pEntryPoint,
		"ps_5_0",
		CompileFlag,
		0,
		&pCode,
		&pError);
	if FAILED(hr)
	{
		ATS_MESSAGE(reinterpret_cast<const char*>(pError->GetBufferPointer()));
	}
	else
	{
		pShaderBinary = ATS_NEW Graphics::ShaderBinary(pCode->GetBufferPointer(), pCode->GetBufferSize());
	}

	ATS_SAFE_RELEASE(pCode);
	ATS_SAFE_RELEASE(pError);

	return pShaderBinary;
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
}
}
