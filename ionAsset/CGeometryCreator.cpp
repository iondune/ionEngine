
#include "CGeometryCreator.h"


CMesh * CGeometryCreator::CreateCube(vec3f const & Size)
{
	static f32 const CubePositions[] =
	{
		-0.5, -0.5, -0.5, // back face verts [0-3]
		-0.5, 0.5, -0.5,
		0.5, 0.5, -0.5,
		0.5, -0.5, -0.5,

		-0.5, -0.5, 0.5, // front face verts [4-7]
		-0.5, 0.5, 0.5,
		0.5, 0.5, 0.5,
		0.5, -0.5, 0.5,

		-0.5, -0.5, 0.5, // left face verts [8-11]
		-0.5, -0.5, -0.5,
		-0.5, 0.5, -0.5,
		-0.5, 0.5, 0.5,

		0.5, -0.5, 0.5, // right face verts [12-15]
		0.5, -0.5, -0.5,
		0.5, 0.5, -0.5,
		0.5, 0.5, 0.5,

		-0.5, 0.5, 0.5, // top face verts [16-19]
		-0.5, 0.5, -0.5,
		0.5, 0.5, -0.5,
		0.5, 0.5, 0.5,

		-0.5, -0.5, 0.5, // bottom face verts [20-23]
		-0.5, -0.5, -0.5,
		0.5, -0.5, -0.5,
		0.5, -0.5, 0.5
	};

	static f32 const CubeNormals[] =
	{
		0, 0, -1, // back face verts [0-3]
		0, 0, -1,
		0, 0, -1,
		0, 0, -1,

		0, 0, 1, // front face verts [4-7]
		0, 0, 1,
		0, 0, 1,
		0, 0, 1,

		-1, 0, 0, // left face verts [8-11]
		-1, 0, 0,
		-1, 0, 0,
		-1, 0, 0,

		1, 0, 0, // right face verts [12-15]
		1, 0, 0,
		1, 0, 0,
		1, 0, 0,

		0, 1, 0, // top face verts [16-19]
		0, 1, 0,
		0, 1, 0,
		0, 1, 0,

		0, -1, 0, // bottom face verts [20-23]
		0, -1, 0,
		0, -1, 0,
		0, -1, 0
	};

	static u16 const CubeIndices[] =
	{
		0, 1, 2, // back face verts [0-3]
		2, 3, 0,

		4, 7, 6, // front face verts [4-7]
		6, 5, 4,

		8, 11, 10, // left face verts [8-11]
		10, 9, 8,

		12, 13, 14, // right face verts [12-15]
		14, 15, 12,

		16, 19, 18, // top face verts [16-19]
		18, 17, 16,

		20, 21, 22, // bottom face verts [20-23]
		22, 23, 20
	};

	SMeshBuffer Buffer;
	for (uint i = 0; i < 24; ++ i)
		Buffer.Vertices.push_back(SVertex(
		vec3f(CubePositions[i * 3 + 0], CubePositions[i * 3 + 1], CubePositions[i * 3 + 2]),
		vec3f(CubeNormals[i * 3 + 0], CubeNormals[i * 3 + 1], CubeNormals[i * 3 + 2])));
	for (uint i = 0; i < 12; ++ i)
		Buffer.Triangles.push_back(SMeshTriangle(
		CubeIndices[i * 3 + 0],
		CubeIndices[i * 3 + 1],
		CubeIndices[i * 3 + 2]));

	return new CMesh(std::move(Buffer));
}

CMesh * CGeometryCreator::CreateCylinder(
	f32 const baseRadius,
	f32 const topRadius,
	f32 const height,
	uint const slices,
	uint const stacks)
{
	std::vector<f32> Positions, Normals;
	std::vector<u32> Indices;

	// Make bottom disc
	Positions.push_back(0.f); Positions.push_back(0.f); Positions.push_back(0.f);
	Normals.push_back(0.f); Normals.push_back(0.f); Normals.push_back(-1.f);

	Positions.push_back(baseRadius); Positions.push_back(0.f); Positions.push_back(0.f);
	Normals.push_back(0.f); Normals.push_back(0.f); Normals.push_back(-1.f);

	for (uint i = 1; i <= slices; ++ i)
	{
		f32 const Angle = (f32) i * 2.f * 3.14159f / (slices);
		Positions.push_back(Cos<f32>(Angle)*baseRadius);
		Positions.push_back(Sin<f32>(Angle)*baseRadius);
		Positions.push_back(0.f);
		Normals.push_back(0.f); Normals.push_back(0.f); Normals.push_back(-1.f);
		Indices.push_back(0);
		Indices.push_back(i + 1);
		Indices.push_back(i + 0);
	}

	// Make top disc
	uint const TopStart = Positions.size() / 3;
	Positions.push_back(0.f); Positions.push_back(0.f); Positions.push_back(height);
	Normals.push_back(0.f); Normals.push_back(0.f); Normals.push_back(1.f);

	Positions.push_back(topRadius); Positions.push_back(0.f); Positions.push_back(height);
	Normals.push_back(0.f); Normals.push_back(0.f); Normals.push_back(1.f);

	for (uint i = 1; i <= slices; ++ i)
	{
		f32 const Angle = (f32) i * 2.f * 3.14159f / slices;
		Positions.push_back(Cos<f32>(Angle)*topRadius);
		Positions.push_back(Sin<f32>(Angle)*topRadius);
		Positions.push_back(height);
		Normals.push_back(0.f); Normals.push_back(0.f); Normals.push_back(1.f);
		Indices.push_back(TopStart);
		Indices.push_back(TopStart + i + 0);
		Indices.push_back(TopStart + i + 1);
	}

	// Make sides
	uint SideStart1 = 0, SideStart2 = 0;
	for (uint j = 0; j <= stacks; ++ j)
	{
		f32 Interpolation = (f32) j / stacks;
		f32 Radius = Interpolation * topRadius + (1.f - Interpolation) * baseRadius;

		SideStart2 = Positions.size() / 3;
		for (uint k = 0; k <= slices; ++ k)
		{
			f32 const Angle = (f32) k * 2.f * 3.14159f / slices;
			Positions.push_back(Cos<f32>(Angle)*Radius);
			Positions.push_back(Sin<f32>(Angle)*Radius);
			Positions.push_back(Interpolation * height);
			Normals.push_back(Cos<f32>(Angle)); Normals.push_back(Sin<f32>(Angle)); Normals.push_back(0.f);
		}

		if (j)
		{
			for (uint k = 0; k < slices; ++ k)
			{
				Indices.push_back(SideStart1 + k);
				Indices.push_back(SideStart1 + k + 1);
				Indices.push_back(SideStart2 + k + 1);

				Indices.push_back(SideStart1 + k);
				Indices.push_back(SideStart2 + k + 1);
				Indices.push_back(SideStart2 + k);
			}
		}
		SideStart1 = SideStart2;
	}

	return new CMesh(SMeshBuffer(Indices, Positions, Normals));
}

CMesh * CGeometryCreator::CreateDisc(
	f32 const innerRadius,
	f32 const outerRadius,
	f32 const height,
	uint const slices,
	uint const stacks)
{
	std::vector<f32> Positions, Normals;
	std::vector<u32> Indices;

	// Make bottom disc
	Positions.push_back(innerRadius); Positions.push_back(0.f); Positions.push_back(0.f);
	Normals.push_back(0.f); Normals.push_back(0.f); Normals.push_back(-1.f);

	Positions.push_back(outerRadius); Positions.push_back(0.f); Positions.push_back(0.f);
	Normals.push_back(0.f); Normals.push_back(0.f); Normals.push_back(-1.f);

	for (uint i = 1; i <= slices; ++ i)
	{
		f32 const Angle = (f32) i * 2.f * 3.14159f / (slices);
		uint const Current = Positions.size() / 3;
		Positions.push_back(Cos<f32>(Angle)*innerRadius);
		Positions.push_back(Sin<f32>(Angle)*innerRadius);
		Positions.push_back(0.f);
		Positions.push_back(Cos<f32>(Angle)*outerRadius);
		Positions.push_back(Sin<f32>(Angle)*outerRadius);
		Positions.push_back(0.f);
		Normals.push_back(0.f); Normals.push_back(0.f); Normals.push_back(-1.f);
		Normals.push_back(0.f); Normals.push_back(0.f); Normals.push_back(-1.f);
		Indices.push_back(Current - 2);
		Indices.push_back(Current - 0);
		Indices.push_back(Current - 1);
		Indices.push_back(Current - 0);
		Indices.push_back(Current + 1);
		Indices.push_back(Current - 1);
	}

	// Make top disc
	Positions.push_back(innerRadius); Positions.push_back(0.f); Positions.push_back(height);
	Normals.push_back(0.f); Normals.push_back(0.f); Normals.push_back(1.f);

	Positions.push_back(outerRadius); Positions.push_back(0.f); Positions.push_back(height);
	Normals.push_back(0.f); Normals.push_back(0.f); Normals.push_back(1.f);

	for (uint i = 1; i <= slices; ++ i)
	{
		f32 const Angle = (f32) i * 2.f * 3.14159f / slices;
		uint const Current = Positions.size() / 3;
		Positions.push_back(Cos<f32>(Angle)*innerRadius);
		Positions.push_back(Sin<f32>(Angle)*innerRadius);
		Positions.push_back(height);
		Positions.push_back(Cos<f32>(Angle)*outerRadius);
		Positions.push_back(Sin<f32>(Angle)*outerRadius);
		Positions.push_back(height);
		Normals.push_back(0.f); Normals.push_back(0.f); Normals.push_back(1.f);
		Normals.push_back(0.f); Normals.push_back(0.f); Normals.push_back(1.f);
		Indices.push_back(Current - 2);
		Indices.push_back(Current - 1);
		Indices.push_back(Current - 0);
		Indices.push_back(Current - 0);
		Indices.push_back(Current - 1);
		Indices.push_back(Current + 1);
	}

	// Make outer sides
	uint SideStart1 = 0, SideStart2 = 0;
	for (uint j = 0; j <= stacks; ++ j)
	{
		f32 Interpolation = (f32) j / stacks;

		SideStart2 = Positions.size() / 3;
		for (uint k = 0; k <= slices; ++ k)
		{
			f32 const Angle = (f32) k * 2.f * 3.14159f / slices;
			Positions.push_back(Cos<f32>(Angle)*outerRadius);
			Positions.push_back(Sin<f32>(Angle)*outerRadius);
			Positions.push_back(Interpolation * height);
			Normals.push_back(Cos<f32>(Angle)); Normals.push_back(Sin<f32>(Angle)); Normals.push_back(0.f);
		}

		if (j)
		{
			for (uint k = 0; k < slices; ++ k)
			{
				Indices.push_back(SideStart1 + k);
				Indices.push_back(SideStart1 + k + 1);
				Indices.push_back(SideStart2 + k + 1);

				Indices.push_back(SideStart1 + k);
				Indices.push_back(SideStart2 + k + 1);
				Indices.push_back(SideStart2 + k);
			}
		}
		SideStart1 = SideStart2;
	}

	// Make inner sides
	SideStart1 = 0, SideStart2 = 0;
	for (uint j = 0; j <= stacks; ++ j)
	{
		f32 Interpolation = (f32) j / stacks;

		SideStart2 = Positions.size() / 3;
		for (uint k = 0; k <= slices; ++ k)
		{
			f32 const Angle = (f32) k * 2.f * 3.14159f / slices;
			Positions.push_back(Cos<f32>(Angle)*innerRadius);
			Positions.push_back(Sin<f32>(Angle)*innerRadius);
			Positions.push_back(Interpolation * height);
			Normals.push_back(-Cos<f32>(Angle)); Normals.push_back(-Sin<f32>(Angle)); Normals.push_back(0.f);
		}

		if (j)
		{
			for (uint k = 0; k < slices; ++ k)
			{
				Indices.push_back(SideStart1 + k);
				Indices.push_back(SideStart2 + k + 1);
				Indices.push_back(SideStart1 + k + 1);

				Indices.push_back(SideStart1 + k);
				Indices.push_back(SideStart2 + k);
				Indices.push_back(SideStart2 + k + 1);
			}
		}
		SideStart1 = SideStart2;
	}

	return new CMesh(SMeshBuffer(Indices, Positions, Normals));
}

CMesh * CGeometryCreator::CreateSphere(vec3f const & Radii, uint const Slices, uint const Stacks)
{
	std::vector<f32> Positions, Normals, TexCoords;
	std::vector<u32> Indices;

	// Make top and bottom points
	Positions.push_back(0.f); Positions.push_back(Radii.Y); Positions.push_back(0.f);
	Normals.push_back(0.f); Normals.push_back(1.f); Normals.push_back(0.f);
	TexCoords.push_back(0); TexCoords.push_back(0.5);

	Positions.push_back(0.f); Positions.push_back(-Radii.Y); Positions.push_back(0.f);
	Normals.push_back(0.f); Normals.push_back(-1.f); Normals.push_back(0.f);
	TexCoords.push_back(0); TexCoords.push_back(0.5);

	for (uint i = 1; i <= Stacks; ++ i)
	{
		f32 const AngleV = (f32) i * 3.14159f / Stacks;
		for (uint j = 0; j <= Slices; ++ j)
		{
			f32 const AngleH = (f32) j * 2.f * 3.14159f / Slices;
			vec3f Radial = vec3f(
				Cos<f32>(AngleH)*Sin<f32>(AngleV),
				Cos<f32>(AngleV),
				Sin<f32>(AngleH)*Sin<f32>(AngleV));
			uint const Start = Positions.size() / 3;
			Positions.push_back(Radial.X*Radii.X);
			Positions.push_back(Radial.Y*Radii.Y);
			Positions.push_back(Radial.Z*Radii.Z);
			Normals.push_back(Radial.X); Normals.push_back(Radial.Y); Normals.push_back(Radial.Z);
			TexCoords.push_back(j / (f32) Slices); TexCoords.push_back((Stacks - i + 1) / (f32) (Stacks + 1));

			if (j)
			{
				if (i == 1)
				{
					Indices.push_back(Start);
					Indices.push_back(Start - 1);
					Indices.push_back(0);
				}
				else
				{
					Indices.push_back(Start);
					Indices.push_back(Start - 1);
					Indices.push_back(Start - Slices - 2);

					Indices.push_back(Start);
					Indices.push_back(Start - Slices - 2);
					Indices.push_back(Start - Slices - 1);
				}

				if (i == Stacks)
				{
					Indices.push_back(Start);
					Indices.push_back(1);
					Indices.push_back(Start - 1);
				}
			}
		}
	}

	return new CMesh(SMeshBuffer(Indices, Positions, Normals, vector<f32>(), TexCoords));
}

CMesh * CGeometryCreator::CreateSkySphere()
{
	CMesh * Mesh = CreateSphere();

	for (auto & Buffer : Mesh->Buffers)
		for (auto & Vertex : Buffer->Vertices)
			Vertex.TextureCoordinates.Y = Abs(Vertex.Position.Y) * 2;

	Mesh->LoadDataIntoBuffers();
	return Mesh;
}

CMesh * CGeometryCreator::CreatePlane(vec2f const & Size)
{
	SMeshBuffer Mesh;
	Mesh.Vertices.resize(4);
	Mesh.Triangles.resize(2);

	Mesh.Vertices[0].Position = vec3f(-0.5, 0, -0.5) * vec3f(Size.X, 1, Size.Y);
	Mesh.Vertices[1].Position = vec3f(-0.5, 0,  0.5) * vec3f(Size.X, 1, Size.Y);
	Mesh.Vertices[2].Position = vec3f( 0.5, 0,  0.5) * vec3f(Size.X, 1, Size.Y);
	Mesh.Vertices[3].Position = vec3f( 0.5, 0, -0.5) * vec3f(Size.X, 1, Size.Y);

	Mesh.Vertices[0].Normal =
		Mesh.Vertices[1].Normal =
		Mesh.Vertices[2].Normal =
		Mesh.Vertices[3].Normal = vec3f(0, 1, 0);

	Mesh.Vertices[0].TextureCoordinates = vec2f(0, 1);
	Mesh.Vertices[1].TextureCoordinates = vec2f(0, 0);
	Mesh.Vertices[2].TextureCoordinates = vec2f(1, 0);
	Mesh.Vertices[3].TextureCoordinates = vec2f(1, 1);

	Mesh.Triangles[0].Indices[0] = 0;
	Mesh.Triangles[0].Indices[1] = 1;
	Mesh.Triangles[0].Indices[2] = 2;

	Mesh.Triangles[1].Indices[0] = 0;
	Mesh.Triangles[1].Indices[1] = 2;
	Mesh.Triangles[1].Indices[2] = 3;

	return new CMesh(std::move(Mesh));
}

CMesh * CGeometryCreator::CreateWafer(f32 const radius, uint const Slices)
{
	SMeshBuffer Mesh;

	Mesh.Vertices.resize(Slices + 1);
	Mesh.Triangles.resize(Slices);

	Mesh.Vertices[0].Position.X = 0;
	Mesh.Vertices[0].Position.Y = 0;
	Mesh.Vertices[0].Position.Z = 0;

	for (uint i = 0; i < Slices; ++ i)
	{
		Mesh.Vertices[i + 1].Position.X = radius * Sin(float(i) / float(Slices) * 2.f * 3.14159f);
		Mesh.Vertices[i + 1].Position.Y = 0;
		Mesh.Vertices[i + 1].Position.Z = radius * Cos(float(i) / float(Slices) * 2.f * 3.14159f);

		Mesh.Vertices[i + 1].Normal = SVector3f(0, 0, 1);

		Mesh.Triangles[i].Indices[0] = 0;
		Mesh.Triangles[i].Indices[1] = i+1;
		Mesh.Triangles[i].Indices[2] = (i == Slices - 1 ? 1 : i+2);
	}

	for (uint i = 0; i < Mesh.Vertices.size(); ++ i)
	{
		Mesh.Vertices[i].TextureCoordinates =
			vec2f(Mesh.Vertices[i].Position.X, Mesh.Vertices[i].Position.Y) / radius / 2 + SVector2f(0.5f);
	}

	return new CMesh(std::move(Mesh));
}
