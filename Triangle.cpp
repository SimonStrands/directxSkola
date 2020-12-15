#include "Triangle.h"

Triangle::Triangle(vertex p0, vertex p1, vertex p2)
{
	for (int i = 0; i < 3; i++) {
		vex[0].getPoints()[i] = p0.pos[i];
		vex[1].getPoints()[i] = p1.pos[i];
		vex[2].getPoints()[i] = p2.pos[i];
	}
}

vec4 Triangle::getNorm()
{
	vec3 tR = vex[0].X(vex[1]);
	tR.Normalize();
	return vec4(tR.getPoints()[0], tR.getPoints()[1], tR.getPoints()[2], 0);
}
