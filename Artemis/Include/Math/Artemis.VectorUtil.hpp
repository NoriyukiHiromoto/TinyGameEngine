#pragma once

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#include "../Artemis.Types.hpp"

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
namespace Artemis
{
namespace Math
{

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
class VectorUtil
{
public:
	static float_t Dot(Vector2 lhs, Vector2 rhs);
	static float_t Cross(Vector2 lhs, Vector2 rhs);
	static Vector2 Normalize(Vector2 rhs);
	static float_t SquareLength(Vector2 value);
	static float_t Length(Vector2 value);
	static Vector2 Min(Vector2 lhs, Vector2 rhs);
	static Vector2 Max(Vector2 lhs, Vector2 rhs);
	static Vector2 Lerp(Vector2 lhs, Vector2 rhs, float_t ratio);

public:
	static float_t Dot(Vector3 lhs, Vector3 rhs);
	static Vector3 Cross(Vector3 lhs, Vector3 rhs);
	static Vector3 Normalize(Vector3 rhs);
	static float_t SquareLength(Vector3 value);
	static float_t Length(Vector3 value);
	static Vector3 Min(Vector3 lhs, Vector3 rhs);
	static Vector3 Max(Vector3 lhs, Vector3 rhs);
	static Vector3 Lerp(Vector3 lhs, Vector3 rhs, float_t ratio);

public:
	static float_t Dot(Vector4 lhs, Vector4 rhs);
	static Vector4 Cross(Vector4 lhs, Vector4 rhs);
	static Vector4 Normalize(Vector4 rhs);
	static float_t SquareLength(Vector4 value);
	static float_t Length(Vector4 value);
	static Vector4 Min(Vector4 lhs, Vector4 rhs);
	static Vector4 Max(Vector4 lhs, Vector4 rhs);
	static Vector4 Lerp(Vector4 lhs, Vector4 rhs, float_t ratio);
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
}
}
