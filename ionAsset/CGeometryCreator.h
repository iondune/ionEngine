
#pragma once

#include "CMesh.h"


class CGeometryCreator
{

public:

	static CMesh * CreateCube(vec3f const & Size = vec3f(1.f));

	static CMesh * CreateCylinder(
		f32 const baseRadius,
		f32 const topRadius,
		f32 const height,
		uint const slices,
		uint const stacks);

	static CMesh * CreateDisc(
		f32 const innerRadius,
		f32 const outerRadius,
		f32 const height,
		uint const slices,
		uint const stacks);

	static CMesh * CreateSphere(
		vec3f const & Radii = vec3f(1.f),
		uint const Slices = 32,
		uint const Stacks = 16);

};
