
#pragma once

#include <ionMath.h>


struct SMeshTriangle
{
	SMeshTriangle();
	SMeshTriangle(uint const index0, uint const index1, uint const index2);

	uint Indices[3];
	vec3f Normal;
};
