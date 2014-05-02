
#pragma once

#include "SMeshBuffer.h"


class CGeometryCreator
{

public:

	static SMeshBuffer * CreateCube(vec3f const & Size = vec3f(1.f));

	static SMeshBuffer * CreateCylinder(
		f32 const baseRadius = 0.2f,
		f32 const topRadius = 0.2f,
		f32 const height = 1.f,
		uint const slices = 32,
		uint const stacks = );

	static SMeshBuffer * CreateDisc(
		f32 const innerRadius = 0.1f,
		f32 const outerRadius = 0.5f,
		f32 const height = 0.2f,
		uint const slices = 32,
		uint const stacks = 4);

	static SMeshBuffer * CreateSphere(
		vec3f const & Radii = vec3f(0.5f),
		uint const Slices = 32,
		uint const Stacks = 16);

	static SMeshBuffer * CreatePlane(
		vec2f const & Size = vec2f(1.f));

	static SMeshBuffer * CreateWafer(
		f32 const radius = 0.5f, uint const Slices = 40);

};
