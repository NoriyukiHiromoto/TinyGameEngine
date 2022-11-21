#pragma once

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#include <cmath>
#include <array>
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
constexpr float_t ATS_PI = 3.1415926535897932384626433832795f;
constexpr float_t ATS_PI2 = 6.283185307179586476925286766559f;

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#define ARRAY_COUNT_OF(a) (sizeof(a)/sizeof(a[0]))

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
inline bool operator == (const PointI& lhs, const PointI& rhs) {
	return (lhs.X == rhs.X) && (lhs.Y == rhs.Y);
}
inline bool operator != (const PointI& lhs, const PointI& rhs) {
	return (lhs.X != rhs.X) || (lhs.Y != rhs.Y);
}

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
inline bool operator == (const SizeI& lhs, const SizeI& rhs) {
	return (lhs.W == rhs.W) && (lhs.H == rhs.H);
}
inline bool operator != (const SizeI& lhs, const SizeI& rhs) {
	return (lhs.W != rhs.W) || (lhs.H != rhs.H);
}

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
inline bool operator == (const RectI& lhs, const RectI& rhs) {
	return (lhs.X == rhs.X) && (lhs.Y == rhs.Y) && (lhs.W == rhs.W) && (lhs.H == rhs.H);
}
inline bool operator != (const RectI& lhs, const RectI& rhs) {
	return (lhs.X != rhs.X) || (lhs.Y != rhs.Y) || (lhs.W != rhs.W) || (lhs.H != rhs.H);
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
struct PointF
{
	float_t X, Y;

	PointF()
		: X(0)
		, Y(0)
	{
	}
	PointF(float_t x, float_t y)
		: X(x)
		, Y(y)
	{
	}
};

struct SizeF
{
	float_t W, H;

	SizeF()
		: W(0)
		, H(0)
	{
	}
	SizeF(float_t w, float_t h)
		: W(w)
		, H(h)
	{
	}
};

struct RectF
{
	float_t X, Y, W, H;

	RectF(float_t x, float_t y, float_t w, float_t h)
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

	RectF Expand(float_t expand) const {
		return RectF(X - expand, Y - expand, W + expand * 2.0f, H + expand * 2.0f);
	}
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
struct Color
{
	static const Color BLACK;
	static const Color WHITE;
	static const Color GRAY;
	static const Color RED;
	static const Color GREEN;
	static const Color BLUE;

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

	float_t R, G, B, A;

	ColorF()
		: R(1.0f)
		, G(1.0f)
		, B(1.0f)
		, A(1.0f)
	{
	}
	ColorF(float_t r, float_t g, float_t b)
		: R(r)
		, G(g)
		, B(b)
		, A(1.0f)
	{
	}
	ColorF(float_t r, float_t g, float_t b, float_t a)
		: R(r)
		, G(g)
		, B(b)
		, A(a)
	{
	}
	ColorF(const Color& color)
		: R(static_cast<float_t>(color.R) / 255.0f)
		, G(static_cast<float_t>(color.G) / 255.0f)
		, B(static_cast<float_t>(color.B) / 255.0f)
		, A(static_cast<float_t>(color.A) / 255.0f)
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
		R = static_cast<float_t>(color.R) / 255.0f;
		G = static_cast<float_t>(color.G) / 255.0f;
		B = static_cast<float_t>(color.B) / 255.0f;
		A = static_cast<float_t>(color.A) / 255.0f;
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

	ColorF operator + (float_t rhs) const {
		return ColorF(
			R + rhs,
			G + rhs,
			B + rhs,
			A + rhs);
	}
	ColorF operator - (float_t rhs) const {
		return ColorF(
			R - rhs,
			G - rhs,
			B - rhs,
			A - rhs);
	}
	ColorF operator * (float_t rhs) const {
		return ColorF(
			R * rhs,
			G * rhs,
			B * rhs,
			A * rhs);
	}
	ColorF operator / (float_t rhs) const {
		return ColorF(
			R / rhs,
			G / rhs,
			B / rhs,
			A / rhs);
	}
	ColorF operator + (const ColorF & rhs) const {
		return ColorF(
			R + rhs.R,
			G + rhs.G,
			B + rhs.B,
			A + rhs.A);
	}
	ColorF operator - (const ColorF & rhs) const {
		return ColorF(
			R - rhs.R,
			G - rhs.G,
			B - rhs.B,
			A - rhs.A);
	}
	ColorF operator * (const ColorF & rhs) const {
		return ColorF(
			R * rhs.R,
			G * rhs.G,
			B * rhs.B,
			A * rhs.A);
	}
	ColorF operator / (const ColorF & rhs) const {
		return ColorF(
			R / rhs.R,
			G / rhs.G,
			B / rhs.B,
			A / rhs.A);
	}
	ColorF& operator += (float_t rhs) {
		R += rhs;
		G += rhs;
		B += rhs;
		A += rhs;
		return *this;
	}
	ColorF& operator -= (float_t rhs) {
		R -= rhs;
		G -= rhs;
		B -= rhs;
		A -= rhs;
		return *this;
	}
	ColorF& operator *= (float_t rhs) {
		R *= rhs;
		G *= rhs;
		B *= rhs;
		A *= rhs;
		return *this;
	}
	ColorF& operator /= (float_t rhs) {
		R /= rhs;
		G /= rhs;
		B /= rhs;
		A /= rhs;
		return *this;
	}
	ColorF& operator += (const ColorF & rhs) {
		R += rhs.R;
		G += rhs.G;
		B += rhs.B;
		A += rhs.A;
		return *this;
	}
	ColorF& operator -= (const ColorF & rhs) {
		R -= rhs.R;
		G -= rhs.G;
		B -= rhs.B;
		A -= rhs.A;
		return *this;
	}
	ColorF& operator *= (const ColorF & rhs) {
		R *= rhs.R;
		G *= rhs.G;
		B *= rhs.B;
		A *= rhs.A;
		return *this;
	}
	ColorF& operator /= (const ColorF & rhs) {
		R /= rhs.R;
		G /= rhs.G;
		B /= rhs.B;
		A /= rhs.A;
		return *this;
	}
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
struct Vector2
{
	float_t X, Y;

	Vector2()
		: X(0.0f)
		, Y(0.0f)
	{
	}
	Vector2(float_t x, float_t y)
		: X(x)
		, Y(y)
	{
	}

	Vector2 operator + (float_t rhs) const {
		return Vector2(
			X + rhs,
			Y + rhs);
	}
	Vector2 operator - (float_t rhs) const {
		return Vector2(
			X - rhs,
			Y - rhs);
	}
	Vector2 operator * (float_t rhs) const {
		return Vector2(
			X * rhs,
			Y * rhs);
	}
	Vector2 operator / (float_t rhs) const {
		return Vector2(
			X / rhs,
			Y / rhs);
	}
	Vector2 operator + (const Vector2& rhs) const {
		return Vector2(
			X + rhs.X,
			Y + rhs.Y);
	}
	Vector2 operator - (const Vector2& rhs) const {
		return Vector2(
			X - rhs.X,
			Y - rhs.Y);
	}
	Vector2 operator * (const Vector2& rhs) const {
		return Vector2(
			X * rhs.X,
			Y * rhs.Y);
	}
	Vector2 operator / (const Vector2& rhs) const {
		return Vector2(
			X / rhs.X,
			Y / rhs.Y);
	}
	Vector2& operator += (float_t rhs) {
		X += rhs;
		Y += rhs;
		return *this;
	}
	Vector2& operator -= (float_t rhs) {
		X -= rhs;
		Y -= rhs;
		return *this;
	}
	Vector2& operator *= (float_t rhs) {
		X *= rhs;
		Y *= rhs;
		return *this;
	}
	Vector2& operator /= (float_t rhs) {
		X /= rhs;
		Y /= rhs;
		return *this;
	}
	Vector2& operator += (const Vector2& rhs) {
		X += rhs.X;
		Y += rhs.Y;
		return *this;
	}
	Vector2& operator -= (const Vector2& rhs) {
		X -= rhs.X;
		Y -= rhs.Y;
		return *this;
	}
	Vector2& operator *= (const Vector2& rhs) {
		X *= rhs.X;
		Y *= rhs.Y;
		return *this;
	}
	Vector2& operator /= (const Vector2& rhs) {
		X /= rhs.X;
		Y /= rhs.Y;
		return *this;
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
	static const Vector3 ZERO;

	float_t X, Y, Z;

	Vector3()
		: X(0.0f)
		, Y(0.0f)
		, Z(0.0f)
	{
	}
	Vector3(float_t x, float_t y, float_t z)
		: X(x)
		, Y(y)
		, Z(z)
	{
	}

	Vector3& operator = (Vector2 rhs)
	{
		X = rhs.X;
		Y = rhs.Y;
		Z = 0.0f;
		return *this;
	}

	Vector2& XY() { return *reinterpret_cast<Vector2*>(this); }
	const Vector2& XY() const { return *reinterpret_cast<const Vector2*>(this); }

	Vector3 operator + (float_t rhs) const {
		return Vector3(
			X + rhs,
			Y + rhs,
			Z + rhs);
	}
	Vector3 operator - (float_t rhs) const {
		return Vector3(
			X - rhs,
			Y - rhs,
			Z - rhs);
	}
	Vector3 operator * (float_t rhs) const {
		return Vector3(
			X * rhs,
			Y * rhs,
			Z * rhs);
	}
	Vector3 operator / (float_t rhs) const {
		return Vector3(
			X / rhs,
			Y / rhs,
			Z / rhs);
	}
	Vector3 operator + (const Vector3& rhs) const {
		return Vector3(
			X + rhs.X,
			Y + rhs.Y,
			Z + rhs.Z);
	}
	Vector3 operator - (const Vector3& rhs) const {
		return Vector3(
			X - rhs.X,
			Y - rhs.Y,
			Z - rhs.Z);
	}
	Vector3 operator * (const Vector3& rhs) const {
		return Vector3(
			X * rhs.X,
			Y * rhs.Y,
			Z * rhs.Z);
	}
	Vector3 operator / (const Vector3& rhs) const {
		return Vector3(
			X / rhs.X,
			Y / rhs.Y,
			Z / rhs.Z);
	}
	Vector3& operator += (float_t rhs) {
		X += rhs;
		Y += rhs;
		Z += rhs;
		return *this;
	}
	Vector3& operator -= (float_t rhs) {
		X -= rhs;
		Y -= rhs;
		Z -= rhs;
		return *this;
	}
	Vector3& operator *= (float_t rhs) {
		X *= rhs;
		Y *= rhs;
		Z *= rhs;
		return *this;
	}
	Vector3& operator /= (float_t rhs) {
		X /= rhs;
		Y /= rhs;
		Z /= rhs;
		return *this;
	}
	Vector3& operator += (const Vector3& rhs) {
		X += rhs.X;
		Y += rhs.Y;
		Z += rhs.Z;
		return *this;
	}
	Vector3& operator -= (const Vector3& rhs) {
		X -= rhs.X;
		Y -= rhs.Y;
		Z -= rhs.Z;
		return *this;
	}
	Vector3& operator *= (const Vector3& rhs) {
		X *= rhs.X;
		Y *= rhs.Y;
		Z *= rhs.Z;
		return *this;
	}
	Vector3& operator /= (const Vector3& rhs) {
		X /= rhs.X;
		Y /= rhs.Y;
		Z /= rhs.Z;
		return *this;
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
	static const Vector4 ZERO;

	float_t X, Y, Z, W;

	Vector4()
		: X(0.0f)
		, Y(0.0f)
		, Z(0.0f)
		, W(1.0f)
	{
	}
	Vector4(float_t x, float_t y, float_t z)
		: X(x)
		, Y(y)
		, Z(z)
		, W(1.0f)
	{
	}
	Vector4(float_t x, float_t y, float_t z, float_t w)
		: X(x)
		, Y(y)
		, Z(z)
		, W(w)
	{
	}

	Vector4& operator = (Vector2 rhs)
	{
		X = rhs.X;
		Y = rhs.Y;
		Z = 0.0f;
		W = 1.0f;
		return *this;
	}
	Vector4& operator = (Vector3 rhs)
	{
		X = rhs.X;
		Y = rhs.Y;
		Z = rhs.Z;
		W = 1.0f;
		return *this;
	}
	Vector4& operator = (Vector4 rhs)
	{
		X = rhs.X;
		Y = rhs.Y;
		Z = rhs.Z;
		W = rhs.W;
		return *this;
	}

	Vector2& XY() { return *reinterpret_cast<Vector2*>(this); }
	Vector3& XYZ() { return *reinterpret_cast<Vector3*>(this); }

	const Vector2& XY() const { return *reinterpret_cast<const Vector2*>(this); }
	const Vector3& XYZ() const { return *reinterpret_cast<const Vector3*>(this); }

	Vector4 operator + (float_t rhs) const {
		return Vector4(
			X + rhs,
			Y + rhs,
			Z + rhs,
			W + rhs);
	}
	Vector4 operator - (float_t rhs) const {
		return Vector4(
			X - rhs,
			Y - rhs,
			Z - rhs,
			W - rhs);
	}
	Vector4 operator * (float_t rhs) const {
		return Vector4(
			X * rhs,
			Y * rhs,
			Z * rhs,
			W * rhs);
	}
	Vector4 operator / (float_t rhs) const {
		return Vector4(
			X / rhs,
			Y / rhs,
			Z / rhs,
			W / rhs);
	}
	Vector4 operator + (const Vector4& rhs) const {
		return Vector4(
			X + rhs.X,
			Y + rhs.Y,
			Z + rhs.Z,
			W + rhs.W);
	}
	Vector4 operator - (const Vector4& rhs) const {
		return Vector4(
			X - rhs.X,
			Y - rhs.Y,
			Z - rhs.Z,
			W - rhs.W);
	}
	Vector4 operator * (const Vector4& rhs) const {
		return Vector4(
			X * rhs.X,
			Y * rhs.Y,
			Z * rhs.Z,
			W * rhs.W);
	}
	Vector4 operator / (const Vector4& rhs) const {
		return Vector4(
			X / rhs.X,
			Y / rhs.Y,
			Z / rhs.Z,
			W / rhs.W);
	}
	Vector4& operator += (float_t rhs) {
		X += rhs;
		Y += rhs;
		Z += rhs;
		W += rhs;
		return *this;
	}
	Vector4& operator -= (float_t rhs) {
		X -= rhs;
		Y -= rhs;
		Z -= rhs;
		W -= rhs;
		return *this;
	}
	Vector4& operator *= (float_t rhs) {
		X *= rhs;
		Y *= rhs;
		Z *= rhs;
		W *= rhs;
		return *this;
	}
	Vector4& operator /= (float_t rhs) {
		X /= rhs;
		Y /= rhs;
		Z /= rhs;
		W /= rhs;
		return *this;
	}
	Vector4& operator += (const Vector4& rhs) {
		X += rhs.X;
		Y += rhs.Y;
		Z += rhs.Z;
		W += rhs.W;
		return *this;
	}
	Vector4& operator -= (const Vector4& rhs) {
		X -= rhs.X;
		Y -= rhs.Y;
		Z -= rhs.Z;
		W -= rhs.W;
		return *this;
	}
	Vector4& operator *= (const Vector4& rhs) {
		X *= rhs.X;
		Y *= rhs.Y;
		Z *= rhs.Z;
		W *= rhs.W;
		return *this;
	}
	Vector4& operator /= (const Vector4& rhs) {
		X /= rhs.X;
		Y /= rhs.Y;
		Z /= rhs.Z;
		W /= rhs.W;
		return *this;
	}
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
struct Matrix
{
	static const Matrix IDENTITY;

	Vector4 X, Y, Z, W;

	Matrix()
		: X(IDENTITY.X)
		, Y(IDENTITY.Y)
		, Z(IDENTITY.Z)
		, W(IDENTITY.W)
	{
	}

	Matrix(const Matrix& rhs)
		: X(rhs.X)
		, Y(rhs.Y)
		, Z(rhs.Z)
		, W(rhs.W)
	{
	}

	Matrix(const Vector4& x, const Vector4& y, const Vector4& z, const Vector4& w)
		: X(x)
		, Y(y)
		, Z(z)
		, W(w)
	{
	}

	Matrix(
		float_t _11, float_t _12, float_t _13, float_t _14,
		float_t _21, float_t _22, float_t _23, float_t _24,
		float_t _31, float_t _32, float_t _33, float_t _34,
		float_t _41, float_t _42, float_t _43, float_t _44)
		: X(_11, _12, _13, _14)
		, Y(_21, _22, _23, _24)
		, Z(_31, _32, _33, _34)
		, W(_41, _42, _43, _44)
	{
	}
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
}
