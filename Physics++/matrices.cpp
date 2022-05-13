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

// Determinants
// Determinant of a 2x2 Matrix
float Determinant(const mat2& matrix)
{
	return matrix._11 * matrix._22 -
		matrix._12 * matrix._21;
}

// Determinant of a 3x3 Matrix
float Determinant(const mat3& matrix)
{
	float result = 0.0f;
	mat3 cofactor = Cofactor(matrix);

	for (int j = 0; j < 3; ++j)
	{
		int index = 3 * 0 + j;
		result += matrix.asArray[index] * cofactor[0][j];
	}

	return result;
}

// Matrix of Minors
mat2 Cut(const mat3& mat, int row, int col)
{
	mat2 result;
	int index = 0;

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (i == row || j == col)
			{
				continue;
			}
			int target = index++;
			int source = 3 * i + j;
			result.asArray[target] = mat.asArray[source];
		}
	}

	return result;
}

mat2 Minor(const mat2& mat)
{
	return mat2(mat._22, mat._21,
		mat._12, mat._11);
}

mat3 Minor(const mat3& mat)
{
	mat3 result;

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++ j)
		{
			result[i][j] = Determinant(Cut(mat, i, j));
		}
	}
}

// Cofactor
// Generic Cofactor
void Cofactor(float* out, const float* minor,
	int rows, int cols)
{
	for (int i= 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			int t = cols * j + i; // Target index
			int s = cols * j + i; // Source index
			float sign = powf(-1.0, i + j); // + or -
			out[t] = minor[s] * sign;
		}
	}
}

// Specific Matrix Cofactors
mat2 Cofactor(const mat2& mat)
{
	mat2 result;
	Cofactor(result.asArray, Minor(mat).asArray, 2, 2);
	return result;
}

mat3 Cofactor(const mat3& mat)
{
	mat3 result;
	Cofactor(result.asArray, Minor(mat).asArray, 3, 3);
	return result;
}

// For operations on 4x4 matrices
mat3 Cut(const mat4& mat, int row, int col)
{
	mat3 result;
	int index = 0;

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (i == row || j == col)
			{
				continue;
			}
			int target = index++;
			int source = 4 * i + j;
			result.asArray[target] = mat.asArray[source];
		}
	}

	return result;
}

mat4 Minor(const mat4& mat)
{
	mat4 result;

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			result[i][j] = Determinant(Cut(mat, i, j));
		}
	}
}

mat4 Cofactor(const mat4& mat)
{
	mat4 result;
	Cofactor(result.asArray, Minor(mat).asArray, 4, 4);
	return result;
}

float Determinant(const mat4& mat)
{
	float result = 0.0f;
	mat4 cofactor = Cofactor(mat);

	for (int j = 0; j < 4; ++j)
	{
		result += mat.asArray[4 * 0 + j] * cofactor[0][j];
	}

	return result;
}