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
class ShaderBinary
	: public IShaderBinary
	, public Common::ReferenceCountObject
{
private:
	std::vector<uint8_t> _Code;

public:
	ShaderBinary(void* pData, size_t DataSize);
	virtual ~ShaderBinary();

	virtual int32_t AddReference() override { return Common::ReferenceCountObject::AddReference(); }
	virtual int32_t Release() override { return Common::ReferenceCountObject::Release(); }
	virtual int32_t GetReference() const override { return Common::ReferenceCountObject::GetReference(); }

	virtual const void* GetCodePointer() const override { return _Code.empty() ? nullptr : &(_Code[0]); }
	virtual uint32_t GetCodeSize() const override { return _Code.empty() ? 0 : static_cast<uint32_t>(_Code.size()); }
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
}
}
