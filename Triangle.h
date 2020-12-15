#pragma once
#include "plHelper.h"
#include "Vec.h"

class Triangle {
public:
	Triangle(vertex p0, vertex p1, vertex p2);
	vec4 getNorm();
private:
	vec3 vex[3];
};