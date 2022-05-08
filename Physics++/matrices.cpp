#include "matrices.h"
#include <cmath>
#include <cfloat>

#define CMP(x, y) (fabsf((x) - (y)) <= FLT_EPSILON * fmaxf(1.0f, fmaxf(fabsf(x), fabsf(y))))

	//		METHOD IMPLEMENTATIONS

// TRANSPOSE
// Generic Transpose
void Transpose(const float* srcMat, float* dstMat,
	int srcRows, int srcCols)
{
	for (int i = 0; i < srcRows * srcCols; i ++)
	{
		int row = i / srcRows;
		int col = i % srcRows;
		dstMat[i] = srcMat[srcCols * col + row];
	}
}

// Specific Matrices Transposes
mat2 Transpose(const mat2& matrix)
{
	mat2 result;
	Transpose(matrix.asArray, result.asArray, 2, 2);
	return result;
}

mat3 Transpose(const mat3& matrix)
{
	mat3 result;
	Transpose(matrix.asArray, result.asArray, 3, 3);
	return result;
}

mat4 Transpose(const mat4& matrix)
{
	mat4 result;
	Transpose(matrix.asArray, result.asArray, 4, 4);
	return result;
}

// Multiplacation
// Scalar Multiplication
mat2 operator* (const mat2& matrix, float scalar)
{
	mat2 result;
	for (int i = 0; i < 4; i++)
	{
		result.asArray[i] = matrix.asArray[i] * scalar;
	}
	return result;
}

mat3 operator* (const mat3& matrix, float scalar)
{
	mat3 result;
	for (int i = 0; i < 9; i++)
	{
		result.asArray[i] = matrix.asArray[i] * scalar;
	}
	return result;
}

mat4 operator* (const mat4& matrix, float scalar)
{
	mat4 result;
	for (int i = 0; i < 16; i++)
	{
		result.asArray[i] = matrix.asArray[i] * scalar;
	}
	return result;
}

// Matrix-Matrix Multiplication
// Generic Multiplication
bool Multiply(float* out, const float* matA, int aRows,
	int aCols, const float* matB, int bRows, int bCols)
{
	if (aCols != bRows)
	{
		return false;
	}

	for (int i = 0; i < aRows; i++)
	{
		for (int j = 0; j < bCols; j++)
		{
			out[bCols * i + j] = 0.0f;
			for (int k = 0; k < bRows; k++)
			{
				int a = aCols * i + k;
				int b = bCols * k + j;
				out[bCols * i + j] += matA[a] * matB[b];
			}
		}
	}

	return true;
}

// Specific Matrix-Matrix Multiplications
mat2 operator* (const mat2& matA, const mat2& matB)
{
	mat2 result;
	Multiply(result.asArray, matA.asArray, 
		2, 2, matB.asArray, 2, 2);
	return result;
}

mat3 operator* (const mat3& matA, const mat3& matB)
{
	mat3 result;
	Multiply(result.asArray, matA.asArray,
		3, 3, matB.asArray, 3, 3);
	return result;
}

mat4 operator* (const mat4& matA, const mat4& matB)
{
	mat4 result;
	Multiply(result.asArray, matA.asArray,
		4, 4, matB.asArray, 4, 4);
	return result;
}