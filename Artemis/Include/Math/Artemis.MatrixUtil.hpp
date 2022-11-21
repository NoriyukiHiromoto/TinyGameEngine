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
class MatrixUtil
{
public:
	static Matrix LookAtLH(Vector3 Eye, Vector3 At, Vector3 Up);
	static Matrix PerspectiveFovLH(float_t FovY, float_t Aspect, float_t NearZ, float_t FarZ);
	static Matrix OrthographicLH(float_t Width, float_t Height, float_t NearZ, float_t FarZ);
	static Matrix Scaling(float_t scale);
	static Matrix Scaling(float_t x, float_t y, float_t z);
	static Matrix RotationX(float_t radian);
	static Matrix RotationY(float_t radian);
	static Matrix RotationZ(float_t radian);
	static Matrix Translation(float_t x, float_t y, float_t z);
	static Matrix Transpose(Matrix In);
	static Matrix Inverse(Matrix In);
	static Matrix Multiply(Matrix lhs, Matrix rhs);
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
}
}
