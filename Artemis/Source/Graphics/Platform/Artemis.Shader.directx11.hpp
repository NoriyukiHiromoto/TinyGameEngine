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
class Shader
	: public IShader
	, public Common::ReferenceCountObject
{
private:
	ID3D11InputLayout* _pInputLayout;
	ID3D11VertexShader* _pVertexShader;
	ID3D11PixelShader* _pPixelShader;

public:
	ID3D11InputLayout* GetInputLayout() const { return _pInputLayout; }
	ID3D11VertexShader* GetVertexShader() const { return _pVertexShader; };
	ID3D11PixelShader* GetPixelShader() const { return _pPixelShader; };

public:
	Shader(ID3D11InputLayout* pInputLayout, ID3D11VertexShader* pVertexShader, ID3D11PixelShader* pPixelShader);
	virtual ~Shader();

	virtual int32_t AddReference() override { return Common::ReferenceCountObject::AddReference(); }
	virtual int32_t Release() override { return Common::ReferenceCountObject::Release(); }
	virtual int32_t GetReference() const override { return Common::ReferenceCountObject::GetReference(); }
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
}
}
