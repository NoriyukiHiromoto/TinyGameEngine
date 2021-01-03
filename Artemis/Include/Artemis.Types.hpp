#pragma once

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#include <cmath>
#include <cstdint>
#include <functional>

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
namespace Artemis
{

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#define SAFE_RELEASE(_ptr_)			{ if (_ptr_ != nullptr) { _ptr_->Release();	_ptr_ = nullptr; } }
#define SAFE_DELETE(_ptr_)			{ if (_ptr_ != nullptr) { delete _ptr_;		_ptr_ = nullptr; } }
#define SAFE_DELETE_ARRAY(_ptr_)	{ if (_ptr_ != nullptr) { delete [] _ptr_;	_ptr_ = nullptr; } }

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
struct PointI
{
	int32_t X, Y;

	PointI()
		: X(0)
		, Y(0)
	{
	}
	PointI(int32_t x, int32_t y)
		: X(x)
		, Y(y)
	{
	}
};

struct SizeI
{
	int32_t W, H;

	SizeI()
		: W(0)
		, H(0)
	{
	}
	SizeI(int32_t w, int32_t h)
		: W(w)
		, H(h)
	{
	}
};

struct RectI
{
	int32_t X, Y, W, H;

	RectI(int32_t x, int32_t y, int32_t w, int32_t h)
		: X(x)
		, Y(y)
		, W(w)
		, H(h)
	{
	}

	PointI Location() const {
		return PointI(X, Y);
	}
	SizeI Size() const {
		return SizeI(W, H);
	}

	RectI Expand(int32_t expand) const {
		return RectI(X - expand, Y - expand, W + expand * 2, H + expand * 2);
	}
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
struct PointF
{
	float X, Y;

	PointF()
		: X(0)
		, Y(0)
	{
	}
	PointF(float x, float y)
		: X(x)
		, Y(y)
	{
	}
};

struct SizeF
{
	float W, H;

	SizeF()
		: W(0)
		, H(0)
	{
	}
	SizeF(float w, float h)
		: W(w)
		, H(h)
	{
	}
};

struct RectF
{
	float X, Y, W, H;

	RectF(float x, float y, float w, float h)
		: X(x)
		, Y(y)
		, W(w)
		, H(h)
	{
	}

	PointF Location() const {
		return PointF(X, Y);
	}
	SizeF Size() const {
		return SizeF(W, H);
	}

	RectF Expand(float expand) const {
		return RectF(X - expand, Y - expand, W + expand * 2.0f, H + expand * 2.0f);
	}
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
struct Color
{
	uint8_t R, G, B, A;

	Color()
		: R(0xFF)
		, G(0xFF)
		, B(0xFF)
		, A(0xFF)
	{
	}
	Color(uint8_t r, uint8_t g, uint8_t b)
		: R(r)
		, G(g)
		, B(b)
		, A(0xFF)
	{
	}
	Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
		: R(r)
		, G(g)
		, B(b)
		, A(a)
	{
	}
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
struct ColorF
{
	static const ColorF BLACK;
	static const ColorF WHITE;
	static const ColorF GRAY;
	static const ColorF RED;
	static const ColorF GREEN;
	static const ColorF BLUE;

	float R, G, B, A;

	ColorF()
		: R(1.0f)
		, G(1.0f)
		, B(1.0f)
		, A(1.0f)
	{
	}
	ColorF(float r, float g, float b)
		: R(r)
		, G(g)
		, B(b)
		, A(1.0f)
	{
	}
	ColorF(float r, float g, float b, float a)
		: R(r)
		, G(g)
		, B(b)
		, A(a)
	{
	}
	ColorF(const Color& color)
		: R(static_cast<float>(color.R) / 255.0f)
		, G(static_cast<float>(color.G) / 255.0f)
		, B(static_cast<float>(color.B) / 255.0f)
		, A(static_cast<float>(color.A) / 255.0f)
	{
	}

	ColorF& operator = (const ColorF& color) {
		R = color.R;
		G = color.G;
		B = color.B;
		A = color.A;
		return *this;
	}
	ColorF& operator = (const Color& color) {
		R = static_cast<float>(color.R) / 255.0f;
		G = static_cast<float>(color.G) / 255.0f;
		B = static_cast<float>(color.B) / 255.0f;
		A = static_cast<float>(color.A) / 255.0f;
		return *this;
	}

	ColorF ToLinear() const {
		return ColorF(
			powf(R, 2.2f),
			powf(G, 2.2f),
			powf(B, 2.2f),
			powf(A, 2.2f));
	}
	ColorF ToGamma() const {
		return ColorF(
			powf(R, 1.0f / 2.2f),
			powf(G, 1.0f / 2.2f),
			powf(B, 1.0f / 2.2f),
			powf(A, 1.0f / 2.2f));
	}
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
struct Vector2
{
	float X, Y;

	Vector2()
		: X(0.0f)
		, Y(0.0f)
	{
	}
	Vector2(float x, float y)
		: X(x)
		, Y(y)
	{
	}
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
struct Vector3
{
	static const Vector3 RIGHT;
	static const Vector3 FORWARD;
	static const Vector3 UP;

	float X, Y, Z;

	Vector3()
		: X(0.0f)
		, Y(0.0f)
		, Z(0.0f)
	{
	}
	Vector3(float x, float y, float z)
		: X(x)
		, Y(y)
		, Z(y)
	{
	}
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
struct Vector4
{
	static const Vector4 RIGHT;
	static const Vector4 FORWARD;
	static const Vector4 UP;

	float X, Y, Z, W;

	Vector4()
		: X(0.0f)
		, Y(0.0f)
		, Z(0.0f)
		, W(1.0f)
	{
	}
	Vector4(float x, float y, float z)
		: X(x)
		, Y(y)
		, Z(y)
		, W(1.0f)
	{
	}
	Vector4(float x, float y, float z, float w)
		: X(x)
		, Y(y)
		, Z(y)
		, W(y)
	{
	}
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
