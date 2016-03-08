
#pragma once

#include "CSimpleMesh.h"


namespace ion
{
	namespace Scene
	{

		class CGeometryCreator
		{

		public:

			static CSimpleMesh * CreateCube(vec3f const & Size = vec3f(1.f));

			static CSimpleMesh * CreateCylinder(
				f32 const baseRadius = 0.2f,
				f32 const topRadius = 0.2f,
				f32 const height = 1.f,
				uint const slices = 32,
				uint const stacks = 4);

			static CSimpleMesh * CreateDisc(
				f32 const innerRadius = 0.1f,
				f32 const outerRadius = 0.5f,
				f32 const height = 0.2f,
				uint const slices = 32,
				uint const stacks = 4);

			static CSimpleMesh * CreateSphere(
				vec3f const & Radii = vec3f(0.5f),
				uint const Slices = 32,
				uint const Stacks = 16);

			static CSimpleMesh * CreateSkySphere();

			static CSimpleMesh * CreatePlane(
				vec2f const & Size = vec2f(1.f));

			static CSimpleMesh * CreateWafer(
				f32 const radius = 0.5f, uint const Slices = 40);

			static CSimpleMesh * Intersect(CSimpleMesh const * A, CSimpleMesh const * B, vec3f const & AOffset = 0, vec3f const & BOffset = 0);

		};

	}
}
