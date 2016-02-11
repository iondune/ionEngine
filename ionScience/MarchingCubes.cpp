
#include "MarchingCubes.h"

#include "MarchingCubesLookupTables.h"
#include "CColorTable.h"


void CalculateGradient(SMarchingCubesVolume & Volume)
{
	for (s32 z = 0; z < Volume.Dimensions.Z; ++ z)
	for (s32 y = 0; y < Volume.Dimensions.Y; ++ y)
	for (s32 x = 0; x < Volume.Dimensions.X; ++ x)
	{
		Volume.Get(x, y, z).Gradient = vec3f(
			Volume.Get(x+1, y, z).Value - Volume.Get(x-1, y, z).Value,
			Volume.Get(x, y+1, z).Value - Volume.Get(x, y-1, z).Value,
			Volume.Get(x, y, z+1).Value - Volume.Get(x, y, z-1).Value) / 2.f;
	}
}

ion::Scene::CSimpleMesh * MarchingCubes(SMarchingCubesVolume & Volume)
{
	CalculateGradient(Volume);

	ion::Scene::CSimpleMesh * Mesh = new ion::Scene::CSimpleMesh();
	int CurrentBuffer = 0;
	Mesh->Vertices.reserve(1 << 14);
	Mesh->Triangles.reserve(1 << 11);

	ion::Scene::CSimpleMesh::SVertex Vertices[12];

	for (s32 z = 0; z < Volume.Dimensions.Z; ++ z)
	for (s32 y = 0; y < Volume.Dimensions.Y; ++ y)
	for (s32 x = 0; x < Volume.Dimensions.X; ++ x)
	{
		int Lookup = 0;

		if ((Volume.Get(x,   y,   z).Value   < 0)) Lookup |= 128;
		if ((Volume.Get(x+1, y,   z).Value   < 0)) Lookup |=  64;
		if ((Volume.Get(x+1, y,   z+1).Value < 0)) Lookup |=  32;
		if ((Volume.Get(x,   y,   z+1).Value < 0)) Lookup |=  16;
		if ((Volume.Get(x,   y+1, z).Value   < 0)) Lookup |=   8;
		if ((Volume.Get(x+1, y+1, z).Value   < 0)) Lookup |=   4;
		if ((Volume.Get(x+1, y+1, z+1).Value < 0)) Lookup |=   2;
		if ((Volume.Get(x,   y+1, z+1).Value < 0)) Lookup |=   1;

		auto Interpolate = [&](s32 const v1x, s32 const v1y, s32 const v1z, s32 const v2x, s32 const v2y, s32 const v2z) -> ion::Scene::CSimpleMesh::SVertex
		{
			static CColorTable ColorTable;

			ion::Scene::CSimpleMesh::SVertex v;
			f32 const d1 = Volume.Get(v1x, v1y, v1z).Value;
			f32 const d2 = Volume.Get(v2x, v2y, v2z).Value;
			f32 ratio = d1 / (d2 - d1);
			if (ratio < 0.f)
				ratio += 1.f;

			v.Position =
				vec3f(vec3i(v1x, v1y, v1z)) * (ratio) +
				vec3f(vec3i(v2x, v2y, v2z)) * (1.f - ratio);
			//v.Color = ColorTable.Get(
			//	Volume.Get(v1x, v1y, v1z).Color * (ratio) +
			//	Volume.Get(v2x, v2y, v2z).Color * (1.f - ratio));
			v.Normal =
				Normalize(Volume.Get(v1x, v1y, v1z).Gradient) * (ratio) +
				Normalize(Volume.Get(v2x, v2y, v2z).Gradient) * (1.f - ratio);

			return v;
		};

		if ((Lookup != 0) && (Lookup != 255))
		{
			if (EdgeTable[Lookup] & 1)    Vertices[0]  = Interpolate(x,   y+1, z+1, x+1, y+1, z+1);
			if (EdgeTable[Lookup] & 2)    Vertices[1]  = Interpolate(x+1, y+1, z+1, x+1, y+1, z);
			if (EdgeTable[Lookup] & 4)    Vertices[2]  = Interpolate(x+1, y+1, z,   x,   y+1, z);
			if (EdgeTable[Lookup] & 8)    Vertices[3]  = Interpolate(x,   y+1, z,   x,   y+1, z+1);
			if (EdgeTable[Lookup] & 16)   Vertices[4]  = Interpolate(x,   y,   z+1, x+1, y,   z+1);
			if (EdgeTable[Lookup] & 32)   Vertices[5]  = Interpolate(x+1, y,   z+1, x+1, y,   z);
			if (EdgeTable[Lookup] & 64)   Vertices[6]  = Interpolate(x+1, y,   z,   x,   y,   z);
			if (EdgeTable[Lookup] & 128)  Vertices[7]  = Interpolate(x,   y,   z,   x,   y,   z+1);
			if (EdgeTable[Lookup] & 256)  Vertices[8]  = Interpolate(x,   y+1, z+1, x,   y,   z+1);
			if (EdgeTable[Lookup] & 512)  Vertices[9]  = Interpolate(x+1, y+1, z+1, x+1, y,   z+1);
			if (EdgeTable[Lookup] & 1024) Vertices[10] = Interpolate(x+1, y+1, z,   x+1, y,   z);
			if (EdgeTable[Lookup] & 2048) Vertices[11] = Interpolate(x,   y+1, z,   x,   y,   z);

			for (u32 i = 0; TriTable[Lookup][i] != -1; i += 3)
			{
				for (u32 j = i; j < (i+3); ++ j)
					Mesh->Vertices.push_back(Vertices[TriTable[Lookup][j]]);

				ion::Scene::CSimpleMesh::STriangle Tri;
				Tri.Indices[0] = (uint) Mesh->Vertices.size() - 3;
				Tri.Indices[1] = (uint) Mesh->Vertices.size() - 2;
				Tri.Indices[2] = (uint) Mesh->Vertices.size() - 1;
				Mesh->Triangles.push_back(Tri);
			}
		}
	}

	return Mesh;
}
