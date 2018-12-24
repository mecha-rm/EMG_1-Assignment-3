#include "Matrix.h"



Mat4::Mat4() // just making an identy matrix
{
	col[0][0] = 1.0f;
	col[0][1] = 0.0f;
	col[0][2] = 0.0f;
	col[0][3] = 0.0f;

	col[1][0] = 0.0f;
	col[1][1] = 1.0f;
	col[1][2] = 0.0f;
	col[1][3] = 0.0f;

	col[2][0] = 0.0f;
	col[2][1] = 0.0f;
	col[2][2] = 1.0f;
	col[2][3] = 0.0f;

	col[3][0] = 0.0f;
	col[3][1] = 0.0f;
	col[3][2] = 0.0f;
	col[3][3] = 1.0f;
}

Mat4::Mat4(const Vector4 right, const Vector4 up, const Vector4 dir, const Vector4 pos)
{
	col[0] = right;
	col[1] = up;
	col[2] = dir;
	col[3] = pos;
}

// Initializing all values for a matrix for your game
Mat4::Mat4(float f0, float f1, float f2, float f3, float f4, float f5, float f6, float f7, float f8, float f9, float f10, float f11, float f12, float f13, float f14, float f15)
{
	col[0][0] = f0;
	col[0][1] = f1;
	col[0][2] = f2;
	col[0][3] = f3;

	col[1][0] = f4;
	col[1][1] = f5;
	col[1][2] = f6;
	col[1][3] = f7;

	col[2][0] = f8;
	col[2][1] = f9;
	col[2][2] = f10;
	col[2][3] = f11;

	col[3][0] = f12;
	col[3][1] = f13;
	col[3][2] = f14;
	col[3][3] = f15;
}

const Vector4& Mat4::operator[](const int index) const
{
	return col[index];
}

Vector4 & Mat4::operator[](const int index)
{
	return col[index];
}

Mat4 Mat4::operator+(const Mat4 & m) const // this const means everything in the matrix class will not be changed
{
	return Mat4(
		col[0] + m[0],
		col[1] + m[1],
		col[2] + m[2],
		col[3] + m[3]);
}

Mat4 Mat4::operator*(const Mat4 & m) const // dot product. rotate on the 'x' axis, then rotate on the 'y' axis
{
	/*
	return Mat4(
        col[0][0] * m[0][0] + col[1][0] * m[0][1] + col[2][0] * m[0][2] + col[3][0] * m[0][3],
        col[0][0] * m[1][0] + col[1][0] * m[1][1] + col[2][0] * m[1][2] + col[3][0] * m[1][3],
        col[0][0] * m[2][0] + col[1][0] * m[2][1] + col[2][0] * m[2][2] + col[3][0] * m[2][3],
        col[0][0] * m[3][0] + col[1][0] * m[3][1] + col[2][0] * m[3][2] + col[3][0] * m[3][3],
        
        col[0][1] * m[0][0] + col[1][1] * m[0][1] + col[2][1] * m[0][2] + col[3][1] * m[0][3],
        col[0][1] * m[1][0] + col[1][1] * m[1][1] + col[2][1] * m[1][2] + col[3][1] * m[1][3],
        col[0][1] * m[2][0] + col[1][1] * m[2][1] + col[2][1] * m[2][2] + col[3][1] * m[2][3],
        col[0][1] * m[3][0] + col[1][1] * m[3][1] + col[2][1] * m[3][2] + col[3][1] * m[3][3],
        
        col[0][2] * m[0][0] + col[1][2] * m[0][1] + col[2][2] * m[0][2] + col[3][2] * m[0][3],
        col[0][2] * m[1][0] + col[1][2] * m[1][1] + col[2][2] * m[1][2] + col[3][2] * m[1][3],
        col[0][2] * m[2][0] + col[1][2] * m[2][1] + col[2][2] * m[2][2] + col[3][2] * m[2][3],
        col[0][2] * m[3][0] + col[1][2] * m[3][1] + col[2][2] * m[3][2] + col[3][2] * m[3][3], 
        
        col[0][3] * m[0][0] + col[1][3] * m[0][1] + col[2][3] * m[0][2] + col[3][3] * m[0][3],
        col[0][3] * m[1][0] + col[1][3] * m[1][1] + col[2][3] * m[1][2] + col[3][3] * m[1][3],
        col[0][3] * m[2][0] + col[1][3] * m[2][1] + col[2][3] * m[2][2] + col[3][3] * m[2][3],
        col[0][3] * m[3][0] + col[1][3] * m[3][1] + col[2][3] * m[3][2] + col[3][3] * m[3][3] );
	*/

	// 'col' is the first matrix, and 'm' the second matrix.
	return Mat4(
		col[0][0] * m[0][0] + col[0][1] * m[1][0] + col[0][2] * m[2][0] + col[0][3] * m[3][0],
		col[0][0] * m[0][1] + col[0][1] * m[1][1] + col[0][2] * m[2][1] + col[0][3] * m[3][1],
		col[0][0] * m[0][2] + col[0][1] * m[1][2] + col[0][2] * m[2][2] + col[0][3] * m[3][2],
		col[0][0] * m[0][3] + col[0][1] * m[1][3] + col[0][2] * m[2][3] + col[0][3] * m[3][3],

		col[1][0] * m[0][0] + col[1][1] * m[1][0] + col[1][2] * m[2][0] + col[1][3] * m[3][0],
		col[1][0] * m[0][1] + col[1][1] * m[1][1] + col[1][2] * m[2][1] + col[1][3] * m[3][1],
		col[1][0] * m[0][2] + col[1][1] * m[1][2] + col[1][2] * m[2][2] + col[1][3] * m[3][2],
		col[1][0] * m[0][3] + col[1][1] * m[1][3] + col[1][2] * m[2][3] + col[1][3] * m[3][3],

		col[2][0] * m[0][0] + col[2][1] * m[1][0] + col[2][2] * m[2][0] + col[2][3] * m[3][0],
		col[2][0] * m[0][1] + col[2][1] * m[1][1] + col[2][2] * m[2][1] + col[2][3] * m[3][1],
		col[2][0] * m[0][2] + col[2][1] * m[1][2] + col[2][2] * m[2][2] + col[2][3] * m[3][2],
		col[2][0] * m[0][3] + col[2][1] * m[1][3] + col[2][2] * m[2][3] + col[2][3] * m[3][3],

		col[3][0] * m[0][0] + col[3][1] * m[1][0] + col[3][2] * m[2][0] + col[3][3] * m[3][0],
		col[3][0] * m[0][1] + col[3][1] * m[1][1] + col[3][2] * m[2][1] + col[3][3] * m[3][1],
		col[3][0] * m[0][2] + col[3][1] * m[1][2] + col[3][2] * m[2][2] + col[3][3] * m[3][2],
		col[3][0] * m[0][3] + col[3][1] * m[1][3] + col[3][2] * m[2][3] + col[3][3] * m[3][3]
	);
}

Mat4 Mat4::operator+=(const Mat4 & m) { return *this = *this + m; }

Mat4 Mat4::operator*=(const Mat4 & m) { return *this = *this * m; }

Mat4 Mat4::getTranspose() const
{
	Mat4 temp;
	// You can just cut out the column and paste it as the row for col to make it easier
	temp[0][0] = col[0][0];
	temp[1][0] = col[0][1];
	temp[2][0] = col[0][2];
	temp[3][0] = col[0][3];

	temp[0][1] = col[1][0];
	temp[1][1] = col[1][1];
	temp[2][1] = col[1][2];
	temp[3][1] = col[1][3];

	temp[0][2] = col[2][0];
	temp[1][2] = col[2][1];
	temp[2][2] = col[2][2];
	temp[3][2] = col[2][3];

	temp[0][3] = col[3][0];
	temp[1][3] = col[3][1];
	temp[2][3] = col[3][2];
	temp[3][3] = col[3][3];

	return temp;
}

