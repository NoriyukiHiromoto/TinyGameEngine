#pragma once

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#include "../Artemis.Types.hpp"
#include "../Interface/Graphics/Artemis.ShaderBinary.hpp"

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
class ShaderCompiler
{
public:
	static Graphics::IShaderBinary* CompileVertexShader(const char* pShaderName, const char* pEntryPoint, const char* pShaderCode);
	static Graphics::IShaderBinary* CompilePixelShader(const char* pShaderName, const char* pEntryPoint, const char* pShaderCode);
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
}
}
