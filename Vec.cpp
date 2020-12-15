#include "Vec.h"

vec4::vec4()
{
	x = y = z = w = 0;
}

vec4::vec4(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

void vec4::Normalize()
{
	double i = sqrt(
		(double)x * (double)x +
		(double)y * (double)y +
		(double)z * (double)z +
		(double)w * (double)w);

		this->x = (float)(x / i);
		this->y = (float)(y / i);
		this->z = (float)(z / i);
		this->w = (float)(w / i);
}

float vec4::operator*(vec4& other)
{
	return(this->x * other.x + this->y * other.y + this->z * other.z + this->w * other.w);
}

vec4 vec4::operator+(vec4& other)
{
	return vec4(this->x + other.x, this->y + other.y, this->z + other.z, this->w + other.w);
}

vec4 vec4::operator-(vec4& other)
{
	return vec4(this->x - other.x, this->y - other.y, this->z - other.z, this->w - other.w);
}

bool vec4::operator==(vec4& other)
{
	return (this->x == other.x && this->y == other.y && this->z == other.z && this->w == other.w);
}

void vec4::operator=(vec4& other)
{
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
	this->w = other.w;
}

float vec4::length()
{ 
	return (float)sqrt((double)(x * x + y * y + z * z + w * w));
}

float* vec4::getPoints()
{
	float *theReturn = new float[4]{
		x,y,z,w
	};
	return theReturn;
}

vec3::vec3()
{
	x = 0; y = 0; z = 0;
}

vec3::vec3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

void vec3::Normalize()
{
	double i = sqrt(
		(double)x * (double)x +
		(double)y * (double)y +
		(double)z * (double)z);

	this->x = (float)(x / i);
	this->y = (float)(y / i);
	this->z = (float)(z / i);
}

vec3 vec3::X(const vec3& other)
{
	float x = (this->y * other.z) - (this->z * other.y);
	float y = (this->z * other.x) - (this->x * other.z);
	float z = (this->x * other.y) - (this->y * other.x);
	return vec3(x,y,z);
}

float vec3::operator*(vec3& other)
{
	return(this->x * other.x + this->y * other.y + this->z * other.z);
}

vec3 vec3::operator+(vec3& other)
{
	return vec3(this->x + other.x, this->y + other.y, this->z + other.z);
}

vec3 vec3::operator-(vec3& other)
{
	return vec3(this->x - other.x, this->y - other.y, this->z - other.z);
}

bool vec3::operator==(vec3& other)
{
	return (this->x == other.x && this->y == other.y && this->z == other.z);
}

void vec3::operator=(vec3& other)
{
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
}

float vec3::length()
{
	return (float)sqrt((double)(x * x + y * y + z * z));
}

float* vec3::getPoints()
{
	float *theReturn = new float[3]{
		x,y,z
	};
	return theReturn;
}
