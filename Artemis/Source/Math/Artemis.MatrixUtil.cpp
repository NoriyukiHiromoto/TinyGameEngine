//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#include <Math/Artemis.MatrixUtil.hpp>
#include <Math/Artemis.VectorUtil.hpp>

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
Matrix MatrixUtil::LookAtLH(Vector3 Eye, Vector3 At, Vector3 Up)
{
	const auto zAxis = VectorUtil::Normalize(At - Eye);
	const auto xAxis = VectorUtil::Normalize(VectorUtil::Cross(Up, zAxis));
	const auto yAxis = VectorUtil::Cross(zAxis, xAxis);

	return Matrix(
		xAxis.X, yAxis.X, zAxis.X, 0.0f,
		xAxis.Y, yAxis.Y, zAxis.Y, 0.0f,
		xAxis.Z, yAxis.Z, zAxis.Z, 0.0f,
		-VectorUtil::Dot(xAxis, Eye), -VectorUtil::Dot(yAxis, Eye), -VectorUtil::Dot(zAxis, Eye), 1.0f);
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
Matrix MatrixUtil::PerspectiveFovLH(float_t FovY, float_t Aspect, float_t NearZ, float_t FarZ)
{
	const auto yScale = 1.0f / tanf(FovY * 0.5f);
	const auto xScale = yScale / Aspect;
	const auto zScale = FarZ / (FarZ - NearZ);

	return Matrix(
		xScale, 0.0f, 0.0f, 0.0f,
		0.0f, yScale, 0.0f, 0.0f,
		0.0f, 0.0f, zScale, 1.0f,
		0.0f, 0.0f, -NearZ * zScale, 0.0f);
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
Matrix MatrixUtil::OrthographicLH(float_t Width, float_t Height, float_t NearZ, float_t FarZ)
{
	const auto xScale = 2.0f / Width;
	const auto yScale = 2.0f / Height;
	const auto zScale = 1.0f / (FarZ - NearZ);

	return Matrix(
		xScale, 0.0f, 0.0f, 0.0f,
		0.0f, yScale, 0.0f, 0.0f,
		0.0f, 0.0f, zScale, 0.0f,
		0.0f, 0.0f, -NearZ * zScale, 1.0f);
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
Matrix MatrixUtil::Scaling(float_t scale)
{
	Matrix Out;
	Out.X.X = scale;
	Out.Y.Y = scale;
	Out.Z.Z = scale;
	return Out;
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
Matrix MatrixUtil::Scaling(float_t x, float_t y, float_t z)
{
	Matrix Out;
	Out.X.X = x;
	Out.Y.Y = y;
	Out.Z.Z = z;
	return Out;
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
Matrix MatrixUtil::RotationX(float_t radian)
{
	const float_t c = cosf(radian);
	const float_t s = sinf(radian);

	Matrix Out;
	Out.Y.Y = c;
	Out.Y.Z = s;
	Out.Z.Y = -s;
	Out.Z.Z = c;
	return Out;
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
Matrix MatrixUtil::RotationY(float_t radian)
{
	const float_t c = cosf(radian);
	const float_t s = sinf(radian);

	Matrix Out;
	Out.X.X = c;
	Out.X.Z = -s;
	Out.Z.X = s;
	Out.Z.Z = c;
	return Out;
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
Matrix MatrixUtil::RotationZ(float_t radian)
{
	const float_t c = cosf(radian);
	const float_t s = sinf(radian);

	Matrix Out;
	Out.X.X = c;
	Out.X.Y = s;
	Out.Y.X = -s;
	Out.Y.Y = c;
	return Out;
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
Matrix MatrixUtil::Translation(float_t x, float_t y, float_t z)
{
	Matrix Out;
	Out.W.X = x;
	Out.W.Y = y;
	Out.W.Z = z;
	return Out;
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
Matrix MatrixUtil::Transpose(Matrix In)
{
	return Matrix(
		In.X.X, In.Y.X, In.Z.X, In.W.X,
		In.X.Y, In.Y.Y, In.Z.Y, In.W.Y,
		In.X.Z, In.Y.Z, In.Z.Z, In.W.Z,
		In.X.W, In.Y.W, In.Z.W, In.W.W);
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
Matrix MatrixUtil::Inverse(Matrix In)
{
	const float_t b11 = +In.Y.Y * (In.Z.Z * In.W.W - In.W.Z * In.Z.W) - In.Y.Z * (In.Z.Y * In.W.W - In.W.Y * In.Z.W) + In.Y.W * (In.Z.Y * In.W.Z - In.W.Y * In.Z.Z);
	const float_t b12 = -In.X.Y * (In.Z.Z * In.W.W - In.W.Z * In.Z.W) + In.X.Z * (In.Z.Y * In.W.W - In.W.Y * In.Z.W) - In.X.W * (In.Z.Y * In.W.Z - In.W.Y * In.Z.Z);
	const float_t b13 = +In.X.Y * (In.Y.Z * In.W.W - In.W.Z * In.Y.W) - In.X.Z * (In.Y.Y * In.W.W - In.W.Y * In.Y.W) + In.X.W * (In.Y.Y * In.W.Z - In.W.Y * In.Y.Z);
	const float_t b14 = -In.X.Y * (In.Y.Z * In.Z.W - In.Z.Z * In.Y.W) + In.X.Z * (In.Y.Y * In.Z.W - In.Z.Y * In.Y.W) - In.X.W * (In.Y.Y * In.Z.Z - In.Z.Y * In.Y.Z);

	const float_t b21 = -In.Y.X * (In.Z.Z * In.W.W - In.W.Z * In.Z.W) + In.Y.Z * (In.Z.X * In.W.W - In.W.X * In.Z.W) - In.Y.W * (In.Z.X * In.W.Z - In.W.X * In.Z.Z);
	const float_t b22 = +In.X.X * (In.Z.Z * In.W.W - In.W.Z * In.Z.W) - In.X.Z * (In.Z.X * In.W.W - In.W.X * In.Z.W) + In.X.W * (In.Z.X * In.W.Z - In.W.X * In.Z.Z);
	const float_t b23 = -In.X.X * (In.Y.Z * In.W.W - In.W.Z * In.Y.W) + In.X.Z * (In.Y.X * In.W.W - In.W.X * In.Y.W) - In.X.W * (In.Y.X * In.W.Z - In.W.X * In.Y.Z);
	const float_t b24 = +In.X.X * (In.Y.Z * In.Z.W - In.Z.Z * In.Y.W) - In.X.Z * (In.Y.X * In.Z.W - In.Z.X * In.Y.W) + In.X.W * (In.Y.X * In.Z.Z - In.Z.X * In.Y.Z);

	const float_t b31 = +In.Y.X * (In.Z.Y * In.W.W - In.W.Y * In.Z.W) - In.Y.Y * (In.Z.X * In.W.W - In.W.X * In.Z.W) + In.Y.W * (In.Z.X * In.W.Y - In.W.X * In.Z.Y);
	const float_t b32 = -In.X.X * (In.Z.Y * In.W.W - In.W.Y * In.Z.W) + In.X.Y * (In.Z.X * In.W.W - In.W.X * In.Z.W) - In.X.W * (In.Z.X * In.W.Y - In.W.X * In.Z.Y);
	const float_t b33 = +In.X.X * (In.Y.Y * In.W.W - In.W.Y * In.Y.W) - In.X.Y * (In.Y.X * In.W.W - In.W.X * In.Y.W) + In.X.W * (In.Y.X * In.W.Y - In.W.X * In.Y.Y);
	const float_t b34 = -In.X.X * (In.Y.Y * In.Z.W - In.Z.Y * In.Y.W) + In.X.Y * (In.Y.X * In.Z.W - In.Z.X * In.Y.W) - In.X.W * (In.Y.X * In.Z.Y - In.Z.X * In.Y.Y);

	const float_t b41 = -In.Y.X * (In.Z.Y * In.W.Z - In.W.Y * In.Z.Z) + In.Y.Y * (In.Z.X * In.W.Z - In.W.X * In.Z.Z) - In.Y.Z * (In.Z.X * In.W.Y - In.W.X * In.Z.Y);
	const float_t b42 = +In.X.X * (In.Z.Y * In.W.Z - In.W.Y * In.Z.Z) - In.X.Y * (In.Z.X * In.W.Z - In.W.X * In.Z.Z) + In.X.Z * (In.Z.X * In.W.Y - In.W.X * In.Z.Y);
	const float_t b43 = -In.X.X * (In.Y.Y * In.W.Z - In.W.Y * In.Y.Z) + In.X.Y * (In.Y.X * In.W.Z - In.W.X * In.Y.Z) - In.X.Z * (In.Y.X * In.W.Y - In.W.X * In.Y.Y);
	const float_t b44 = +In.X.X * (In.Y.Y * In.Z.Z - In.Z.Y * In.Y.Z) - In.X.Y * (In.Y.X * In.Z.Z - In.Z.X * In.Y.Z) + In.X.Z * (In.Y.X * In.Z.Y - In.Z.X * In.Y.Y);

	const float_t Det = (In.X.X * b11) + (In.X.Y * b21) + (In.X.Z * b31) + (In.X.W * b41);
	if (fabsf(Det) < FLT_MIN)
	{
		Matrix Out;
		Out.W.X = -In.W.X;
		Out.W.Y = -In.W.Y;
		Out.W.Z = -In.W.Z;
		return Out;
	}
	else
	{
		const float_t InvDet = 1.0f / Det;
		return Matrix(
			b11 * InvDet, b12 * InvDet, b13 * InvDet, b14 * InvDet,
			b21 * InvDet, b22 * InvDet, b23 * InvDet, b24 * InvDet,
			b31 * InvDet, b32 * InvDet, b33 * InvDet, b34 * InvDet,
			b41 * InvDet, b42 * InvDet, b43 * InvDet, b44 * InvDet);
	}
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
Matrix MatrixUtil::Multiply(Matrix lhs, Matrix rhs)
{
	return Matrix(
		(lhs.X.X * rhs.X.X) + (lhs.X.Y * rhs.Y.X) + (lhs.X.Z * rhs.Z.X) + (lhs.X.W * rhs.W.X),
		(lhs.X.X * rhs.X.Y) + (lhs.X.Y * rhs.Y.Y) + (lhs.X.Z * rhs.Z.Y) + (lhs.X.W * rhs.W.Y),
		(lhs.X.X * rhs.X.Z) + (lhs.X.Y * rhs.Y.Z) + (lhs.X.Z * rhs.Z.Z) + (lhs.X.W * rhs.W.Z),
		(lhs.X.X * rhs.X.W) + (lhs.X.Y * rhs.Y.W) + (lhs.X.Z * rhs.Z.W) + (lhs.X.W * rhs.W.W),
		(lhs.Y.X * rhs.X.X) + (lhs.Y.Y * rhs.Y.X) + (lhs.Y.Z * rhs.Z.X) + (lhs.Y.W * rhs.W.X),
		(lhs.Y.X * rhs.X.Y) + (lhs.Y.Y * rhs.Y.Y) + (lhs.Y.Z * rhs.Z.Y) + (lhs.Y.W * rhs.W.Y),
		(lhs.Y.X * rhs.X.Z) + (lhs.Y.Y * rhs.Y.Z) + (lhs.Y.Z * rhs.Z.Z) + (lhs.Y.W * rhs.W.Z),
		(lhs.Y.X * rhs.X.W) + (lhs.Y.Y * rhs.Y.W) + (lhs.Y.Z * rhs.Z.W) + (lhs.Y.W * rhs.W.W),
		(lhs.Z.X * rhs.X.X) + (lhs.Z.Y * rhs.Y.X) + (lhs.Z.Z * rhs.Z.X) + (lhs.Z.W * rhs.W.X),
		(lhs.Z.X * rhs.X.Y) + (lhs.Z.Y * rhs.Y.Y) + (lhs.Z.Z * rhs.Z.Y) + (lhs.Z.W * rhs.W.Y),
		(lhs.Z.X * rhs.X.Z) + (lhs.Z.Y * rhs.Y.Z) + (lhs.Z.Z * rhs.Z.Z) + (lhs.Z.W * rhs.W.Z),
		(lhs.Z.X * rhs.X.W) + (lhs.Z.Y * rhs.Y.W) + (lhs.Z.Z * rhs.Z.W) + (lhs.Z.W * rhs.W.W),
		(lhs.W.X * rhs.X.X) + (lhs.W.Y * rhs.Y.X) + (lhs.W.Z * rhs.Z.X) + (lhs.W.W * rhs.W.X),
		(lhs.W.X * rhs.X.Y) + (lhs.W.Y * rhs.Y.Y) + (lhs.W.Z * rhs.Z.Y) + (lhs.W.W * rhs.W.Y),
		(lhs.W.X * rhs.X.Z) + (lhs.W.Y * rhs.Y.Z) + (lhs.W.Z * rhs.Z.Z) + (lhs.W.W * rhs.W.Z),
		(lhs.W.X * rhs.X.W) + (lhs.W.Y * rhs.Y.W) + (lhs.W.Z * rhs.Z.W) + (lhs.W.W * rhs.W.W));
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
}
}
