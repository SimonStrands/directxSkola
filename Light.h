#pragma once
#include "mat.h"

class PointLight {
public:
	PointLight(vec32 pos);
	vec32 getPos();
private:
	vec32 pos;
};