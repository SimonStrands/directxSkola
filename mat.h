#pragma once
#include "Vec.h"

class Matrix4x4 {
public:
	Matrix4x4();
	Matrix4x4(vec4 *vecs);
	Matrix4x4(vec4 vec1, vec4 vec2, vec4 vec3, vec4 vec5);
	Matrix4x4(float mat[4][4]);
	Matrix4x4(float** mat);
	Matrix4x4 operator*(Matrix4x4 other);
	Matrix4x4 operator*(float mat[4][4]);
	vec4 operator*(vec4 other);
	void operator=(Matrix4x4 *other);
	float** GetMatrix();
private:
	float mat[4][4] = {
		{1,0,0,0},
		{0,1,0,0},
		{0,0,1,0},
		{0,0,0,1},
	};
};
class Matrix3x3 {
	Matrix3x3();
	Matrix3x3(vec3* vecs);
	Matrix3x3(vec3 vec1, vec3 vec2, vec3 vec3p);
	Matrix3x3(float mat[3][3]);
	Matrix3x3(float **mat);
	Matrix3x3 operator*(Matrix3x3& other);
	float* operator*(vec3& other);
	float** GetMatrix();
private:
	float mat[3][3] = {
		{1,0,0},
		{0,1,0},
		{0,0,1}
	};
};