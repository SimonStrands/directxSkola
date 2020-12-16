#pragma once
#include <math.h>
//meant to be vec3.2 techer doesnt want us to have public floats but idc
struct vec32 {
	vec32(float a, float b, float c) {
		this->x = a;
		this->y = b;
		this->z = c;
	}
	float x;
	float y;
	float z;
};

class vec3{
public:
	vec3();
	vec3(float x, float y, float z);
public:
	void Normalize();
	vec3 X(const vec3& other);
	float operator*(vec3& other);
	vec3 operator+(vec3& other);
	vec3 operator-(vec3& other);
	bool operator==(vec3& other);
	void operator=(vec3& other);
	float length();
	float* getPoints();
private:
	float x, y, z;
};
class vec4 {
public:
	vec4();
	vec4(float x, float y, float z, float w);
public:
	void Normalize();
	float operator*(vec4 &other);
	vec4 operator+(vec4 &other);
	vec4 operator-(vec4 &other);
	bool operator==(vec4 &other);
	void operator=(vec4 &other);
	float length();
	float* getPoints();
	float x, y, z, w;
private:
	
};