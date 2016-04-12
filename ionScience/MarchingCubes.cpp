
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

	vec3i VertexIndices[8] =
	{
		vec3i(0, 0, 0),
		vec3i(1, 0, 0),
		vec3i(1, 0, 1),
		vec3i(0, 0, 1),
		vec3i(0, 1, 0),
		vec3i(1, 1, 0),
		vec3i(1, 1, 1),
		vec3i(0, 1, 1),
	};

	for (s32 z = 0; z < Volume.Dimensions.Z; ++ z)
	for (s32 y = 0; y < Volume.Dimensions.Y; ++ y)
	for (s32 x = 0; x < Volume.Dimensions.X; ++ x)
	{
		int Lookup = 0;

		if ((Volume.Get(vec3i(x, y, z) + VertexIndices[0]).Value < 0)) Lookup |=   1;
		if ((Volume.Get(vec3i(x, y, z) + VertexIndices[1]).Value < 0)) Lookup |=   2;
		if ((Volume.Get(vec3i(x, y, z) + VertexIndices[2]).Value < 0)) Lookup |=   4;
		if ((Volume.Get(vec3i(x, y, z) + VertexIndices[3]).Value < 0)) Lookup |=   8;
		if ((Volume.Get(vec3i(x, y, z) + VertexIndices[4]).Value < 0)) Lookup |=  16;
		if ((Volume.Get(vec3i(x, y, z) + VertexIndices[5]).Value < 0)) Lookup |=  32;
		if ((Volume.Get(vec3i(x, y, z) + VertexIndices[6]).Value < 0)) Lookup |=  64;
		if ((Volume.Get(vec3i(x, y, z) + VertexIndices[7]).Value < 0)) Lookup |= 128;

		auto Interpolate = [&](vec3i const & v1, vec3i const & v2) -> ion::Scene::CSimpleMesh::SVertex
		{
			//static CColorTable ColorTable;

			ion::Scene::CSimpleMesh::SVertex v;
			f32 const d1 = Volume.Get(v1).Value;
			f32 const d2 = Volume.Get(v2).Value;
			f32 ratio = d1 / (d2 - d1);
			if (ratio < 0.f)
				ratio += 1.f;

			v.Position =
				vec3f(v1) * (ratio) +
				vec3f(v2) * (1.f - ratio);
			//v.Color = ColorTable.Get(
			//	Volume.Get(v1x, v1y, v1z).Color * (ratio) +
			//	Volume.Get(v2x, v2y, v2z).Color * (1.f - ratio));
			v.Normal =
				Normalize(Volume.Get(v1).Gradient) * (ratio) +
				Normalize(Volume.Get(v2).Gradient) * (1.f - ratio);

			//f32 const valp1 = Volume.Get(v1).Value;
			//f32 const valp2 = Volume.Get(v2).Value;

			//vec3f p1 = vec3f(v1);
			//vec3f p2 = vec3f(v2);

			//float mu;

			//if (abs(0 - valp1) < 0.00001)
			//	return(p1);
			//if (abs(0 - valp2) < 0.00001)
			//	return(p2);
			//if (abs(valp1 - valp2) < 0.00001)
			//	return(p1);
			//mu = (0 - valp1) / (valp2 - valp1);
			//v.Position.X = p1.X + mu * (p2.X - p1.X);
			//v.Position.Y = p1.Y + mu * (p2.Y - p1.Y);
			//v.Position.Z = p1.Z + mu * (p2.Z - p1.Z);

			return v;
		};

		u32 EdgeTableLookup = EdgeTable[Lookup];
		if (EdgeTable[Lookup] != 0)
		{
			if (EdgeTable[Lookup] & 1)    Vertices[0]  = Interpolate(vec3i(x, y, z) + VertexIndices[0], vec3i(x, y, z) + VertexIndices[1]);
			if (EdgeTable[Lookup] & 2)    Vertices[1]  = Interpolate(vec3i(x, y, z) + VertexIndices[1], vec3i(x, y, z) + VertexIndices[2]);
			if (EdgeTable[Lookup] & 4)    Vertices[2]  = Interpolate(vec3i(x, y, z) + VertexIndices[2], vec3i(x, y, z) + VertexIndices[3]);
			if (EdgeTable[Lookup] & 8)    Vertices[3]  = Interpolate(vec3i(x, y, z) + VertexIndices[3], vec3i(x, y, z) + VertexIndices[0]);
			if (EdgeTable[Lookup] & 16)   Vertices[4]  = Interpolate(vec3i(x, y, z) + VertexIndices[4], vec3i(x, y, z) + VertexIndices[5]);
			if (EdgeTable[Lookup] & 32)   Vertices[5]  = Interpolate(vec3i(x, y, z) + VertexIndices[5], vec3i(x, y, z) + VertexIndices[6]);
			if (EdgeTable[Lookup] & 64)   Vertices[6]  = Interpolate(vec3i(x, y, z) + VertexIndices[6], vec3i(x, y, z) + VertexIndices[7]);
			if (EdgeTable[Lookup] & 128)  Vertices[7]  = Interpolate(vec3i(x, y, z) + VertexIndices[7], vec3i(x, y, z) + VertexIndices[4]);
			if (EdgeTable[Lookup] & 256)  Vertices[8]  = Interpolate(vec3i(x, y, z) + VertexIndices[0], vec3i(x, y, z) + VertexIndices[4]);
			if (EdgeTable[Lookup] & 512)  Vertices[9]  = Interpolate(vec3i(x, y, z) + VertexIndices[1], vec3i(x, y, z) + VertexIndices[5]);
			if (EdgeTable[Lookup] & 1024) Vertices[10] = Interpolate(vec3i(x, y, z) + VertexIndices[2], vec3i(x, y, z) + VertexIndices[6]);
			if (EdgeTable[Lookup] & 2048) Vertices[11] = Interpolate(vec3i(x, y, z) + VertexIndices[3], vec3i(x, y, z) + VertexIndices[7]);

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
