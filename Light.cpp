#include "Light.h"

PointLight::PointLight(vec32 pos):
pos(pos)
{
}

vec32 PointLight::getPos()
{
	return this->pos;
}


