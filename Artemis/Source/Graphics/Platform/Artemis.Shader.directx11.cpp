﻿
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
Shader::Shader(ID3D11InputLayout* pInputLayout, ID3D11VertexShader* pVertexShader, ID3D11PixelShader* pPixelShader)
	: _pInputLayout(pInputLayout)
	, _pVertexShader(pVertexShader)
	, _pPixelShader(pPixelShader)
{
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
Shader::~Shader()
{
	ATS_SAFE_RELEASE(_pInputLayout);
	ATS_SAFE_RELEASE(_pVertexShader);
	ATS_SAFE_RELEASE(_pPixelShader);
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
}
}
