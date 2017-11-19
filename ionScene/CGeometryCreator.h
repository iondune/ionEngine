
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
				float const baseRadius = 0.2f,
				float const topRadius = 0.2f,
				float const height = 1.f,
				uint const slices = 32,
				uint const stacks = 4);

			static CSimpleMesh * CreateDisc(
				float const innerRadius = 0.1f,
				float const outerRadius = 0.5f,
				float const height = 0.2f,
				uint const slices = 32,
				uint const stacks = 4);

			static CSimpleMesh * CreateTorus(
				float const centralRadius = 1.f,
				float const innerRadius = 0.25f,
				uint const slices = 16,
				uint const stacks = 20);

			static CSimpleMesh * CreateSphere(
				vec3f const & Radii = vec3f(0.5f),
				uint const Slices = 32,
				uint const Stacks = 16);

			static CSimpleMesh * CreateSkySphere();

			static CSimpleMesh * CreatePlane(
				vec2f const & Size = vec2f(1.f));

			static CSimpleMesh * CreateWafer(
				float const radius = 0.5f, uint const Slices = 40);

			static CSimpleMesh * CreateScreenTriangle();

			static CSimpleMesh * Intersect(CSimpleMesh const * A, CSimpleMesh const * B, vec3f const & AOffset = 0, vec3f const & BOffset = 0);

			static void IntersectAndDelete(CSimpleMesh * A, CSimpleMesh const * B, vec3f const & BOffset = 0);

			static vector<pair<string, CSimpleMesh *>> LoadOBJFileWithNames(string const & FileName, string const & Path = "");
			static vector<CSimpleMesh *> LoadOBJFile(string const & FileName, string const & Path = "");

		};

	}
}
