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
class Buffer
	: public IBuffer
	, public Common::ReferenceCountObject
{
private:
	ID3D11Buffer* _pBuffer;
	eBufferType _BufferType;

public:
	ID3D11Buffer* GetNativePointer() { return _pBuffer; }

public:
	Buffer(eBufferType BufferType, ID3D11Buffer* pBuffer);
	virtual ~Buffer();

	virtual int32_t AddReference() override { return Common::ReferenceCountObject::AddReference(); }
	virtual int32_t Release() override { return Common::ReferenceCountObject::Release(); }
	virtual int32_t GetReference() const override { return Common::ReferenceCountObject::GetReference(); }

	virtual eBufferType BufferType() const override { return _BufferType; }
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
}
}
