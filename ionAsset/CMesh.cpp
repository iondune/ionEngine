
#include "CMesh.h"


CMesh::CMesh()
{}

uint CMesh::GetVertexCount() const
{
	return MeshBuffer.Vertices.size() + 	std::accumulate(Children.begin(), Children.end(), 0, [](uint Count, CMesh * Mesh)
	{
		return Count + Mesh->MeshBuffer.Vertices.size();
	});
}

SBoundingBox3f CMesh::GetBoundingBox() const
{
	SBoundingBox3f Box(SVector3f(std::numeric_limits<float>().max()), SVector3f(-std::numeric_limits<float>().max()));

	for (std::vector<sharedPtr<SMeshBuffer>>::const_iterator bit = MeshBuffers.begin(); bit != MeshBuffers.end(); ++ bit)
		for (std::vector<SVertex>::const_iterator it = (* bit)->Vertices.begin(); it != (* bit)->Vertices.end(); ++ it)
			Box.AddInternalPoint(it->Position);

	return Box;
}

SVector3f CMesh::GetExtent() const
{
	SVector3f Min(std::numeric_limits<float>::max()), Max(-std::numeric_limits<float>::max());
	{
		for (std::vector<sharedPtr<SMeshBuffer>>::const_iterator bit = MeshBuffers.begin(); bit != MeshBuffers.end(); ++ bit)
			for (std::vector<SVertex>::const_iterator it = (* bit)->Vertices.begin(); it != (* bit)->Vertices.end(); ++ it)
			{
				if (Min.X > it->Position.X)
					Min.X = it->Position.X;
				if (Min.Y > it->Position.Y)
					Min.Y = it->Position.Y;
				if (Min.Z > it->Position.Z)
					Min.Z = it->Position.Z;

				if (Max.X < it->Position.X)
					Max.X = it->Position.X;
				if (Max.Y < it->Position.Y)
					Max.Y = it->Position.Y;
				if (Max.Z < it->Position.Z)
					Max.Z = it->Position.Z;
			}
	}

	return (Max - Min);
}

void CMesh::CenterMeshByAverage(vec3f const & CenterLocation)
{
	SVector3f VertexSum;
	for (std::vector<sharedPtr<SMeshBuffer>>::const_iterator bit = MeshBuffers.begin(); bit != MeshBuffers.end(); ++ bit)
		for (std::vector<SVertex>::const_iterator it = (* bit)->Vertices.begin(); it != (* bit)->Vertices.end(); ++ it)
			VertexSum += it->Position;

	VertexSum /= (f32) GetVertexCount();
	SVector3f VertexOffset = CenterLocation - VertexSum;
	for (std::vector<sharedPtr<SMeshBuffer>>::iterator bit = MeshBuffers.begin(); bit != MeshBuffers.end(); ++ bit)
		for (std::vector<SVertex>::iterator it = (* bit)->Vertices.begin(); it != (* bit)->Vertices.end(); ++ it)
			it->Position += VertexOffset;
}

void CMesh::CenterMeshByExtents(vec3f const & CenterLocation)
{
	SVector3f Min(std::numeric_limits<f32>::max()), Max(-std::numeric_limits<f32>::max());
	{
		for (std::vector<sharedPtr<SMeshBuffer>>::const_iterator bit = MeshBuffers.begin(); bit != MeshBuffers.end(); ++ bit)
			for (std::vector<SVertex>::const_iterator it = (* bit)->Vertices.begin(); it != (* bit)->Vertices.end(); ++ it)
			{
				if (Min.X > it->Position.X)
					Min.X = it->Position.X;
				if (Min.Y > it->Position.Y)
					Min.Y = it->Position.Y;
				if (Min.Z > it->Position.Z)
					Min.Z = it->Position.Z;

				if (Max.X < it->Position.X)
					Max.X = it->Position.X;
				if (Max.Y < it->Position.Y)
					Max.Y = it->Position.Y;
				if (Max.Z < it->Position.Z)
					Max.Z = it->Position.Z;
			}
	}

	SVector3f Center = (Max + Min) / 2;

	SVector3f VertexOffset = CenterLocation - Center;
	for (std::vector<sharedPtr<SMeshBuffer>>::iterator bit = MeshBuffers.begin(); bit != MeshBuffers.end(); ++ bit)
		for (std::vector<SVertex>::iterator it = (* bit)->Vertices.begin(); it != (* bit)->Vertices.end(); ++ it)
			it->Position += VertexOffset;
}

void CMesh::ResizeMesh(vec3f const & Scale)
{
	SVector3f Extent = GetExtent();
	SVector3f Resize = Scale / std::max(Extent.X, std::max(Extent.Y, Extent.Z));
	for (std::vector<sharedPtr<SMeshBuffer>>::iterator bit = MeshBuffers.begin(); bit != MeshBuffers.end(); ++ bit)
		for (std::vector<SVertex>::iterator it = (* bit)->Vertices.begin(); it != (* bit)->Vertices.end(); ++ it)
			it->Position *= Resize;
}

void CMesh::ReverseFaces()
{
	for (std::vector<sharedPtr<SMeshBuffer>>::iterator bit = MeshBuffers.begin(); bit != MeshBuffers.end(); ++ bit)
	{
		for (std::vector<SMeshTriangle>::iterator it = (* bit)->Triangles.begin(); it != (* bit)->Triangles.end(); ++ it)
		{
			u32 temp = it->Indices[1];
			it->Indices[1] = it->Indices[2];
			it->Indices[2] = temp;
		}
	}
}

void CMesh::LinearizeIndices()
{
	for (std::vector<sharedPtr<SMeshBuffer>>::iterator bit = MeshBuffers.begin(); bit != MeshBuffers.end(); ++ bit)
	{
		std::vector<SVertex> newVertices;
		std::vector<SMeshTriangle> newTriangles;

		for (std::vector<SMeshTriangle>::iterator it = (* bit)->Triangles.begin(); it != (* bit)->Triangles.end(); ++ it)
		{
			for (int i = 0; i < 3; ++ i)
				newVertices.push_back((* bit)->Vertices[it->Indices[i]]);
		}

		for (uint i = 0; i < newVertices.size() / 3; ++ i)
		{
			SMeshTriangle tri;
			tri.Indices[0] = i * 3;
			tri.Indices[1] = i * 3 + 1;
			tri.Indices[2] = i * 3 + 2;
			newTriangles.push_back(tri);
		}

		(* bit)->Vertices = newVertices;
		(* bit)->Triangles = newTriangles;
	}
}

void CMesh::CalculateNormalsPerFace()
{
	for (std::vector<sharedPtr<SMeshBuffer>>::iterator bit = MeshBuffers.begin(); bit != MeshBuffers.end(); ++ bit)
	{
		for (std::vector<SMeshTriangle>::iterator it = (* bit)->Triangles.begin(); it != (* bit)->Triangles.end(); ++ it)
		{
			it->Normal = ((* bit)->Vertices[it->Indices[1]].Position - (* bit)->Vertices[it->Indices[0]].Position).
				CrossProduct((* bit)->Vertices[it->Indices[2]].Position - (* bit)->Vertices[it->Indices[0]].Position);
			(* bit)->Vertices[it->Indices[0]].Normal = (* bit)->Vertices[it->Indices[1]].Normal = (* bit)->Vertices[it->Indices[2]].Normal = it->Normal;
		}
	}

	for (std::vector<sharedPtr<SMeshBuffer>>::iterator bit = MeshBuffers.begin(); bit != MeshBuffers.end(); ++ bit)
		for (std::vector<SVertex>::iterator it = (* bit)->Vertices.begin(); it != (* bit)->Vertices.end(); ++ it) {
			it->Normal.Normalize();
		}
}

void CMesh::CalculateNormalsPerVertex(bool CombineNear, f32 const NearTolerance)
{
	CalculateNormalsPerFace();

	for (std::vector<sharedPtr<SMeshBuffer>>::iterator bit = MeshBuffers.begin(); bit != MeshBuffers.end(); ++ bit)
		for (std::vector<SVertex>::iterator it = (* bit)->Vertices.begin(); it != (* bit)->Vertices.end(); ++ it)
			it->Normal = SVector3f();

	for (std::vector<sharedPtr<SMeshBuffer>>::iterator bit = MeshBuffers.begin(); bit != MeshBuffers.end(); ++ bit)
		for (std::vector<SMeshTriangle>::iterator it = (* bit)->Triangles.begin(); it != (* bit)->Triangles.end(); ++ it)
			for (int i = 0; i < 3; ++ i)
				(* bit)->Vertices[it->Indices[i]].Normal += it->Normal;

	if (CombineNear)
		for (std::vector<sharedPtr<SMeshBuffer>>::iterator bit = MeshBuffers.begin(); bit != MeshBuffers.end(); ++ bit)
			for (uint i = 0; i < (* bit)->Vertices.size(); ++ i)
				for (uint j = i + 1; j < (* bit)->Vertices.size(); ++ j)
					if ((* bit)->Vertices[i].Position.Equals((* bit)->Vertices[j].Position, NearTolerance))
						(* bit)->Vertices[i].Normal = (* bit)->Vertices[j].Normal = (* bit)->Vertices[i].Normal + (* bit)->Vertices[j].Normal;


	for (std::vector<sharedPtr<SMeshBuffer>>::iterator bit = MeshBuffers.begin(); bit != MeshBuffers.end(); ++ bit)
		for (std::vector<SVertex>::iterator it = (* bit)->Vertices.begin(); it != (* bit)->Vertices.end(); ++ it)
			it->Normal.Normalize();
}


void CMesh::CalculateTextureCoordinates(vec3f const & uVec, vec3f const & vVec, vec2f const & Scale)
{
	SVector3f Min(std::numeric_limits<float>::max()), Max(-std::numeric_limits<float>::max());
	{
		for (std::vector<sharedPtr<SMeshBuffer>>::const_iterator bit = MeshBuffers.begin(); bit != MeshBuffers.end(); ++ bit)
			for (std::vector<SVertex>::const_iterator it = (* bit)->Vertices.begin(); it != (* bit)->Vertices.end(); ++ it)
			{
				if (Min.X > it->Position.X)
					Min.X = it->Position.X;
				if (Min.Y > it->Position.Y)
					Min.Y = it->Position.Y;
				if (Min.Z > it->Position.Z)
					Min.Z = it->Position.Z;

				if (Max.X < it->Position.X)
					Max.X = it->Position.X;
				if (Max.Y < it->Position.Y)
					Max.Y = it->Position.Y;
				if (Max.Z < it->Position.Z)
					Max.Z = it->Position.Z;
			}
	}

	for (std::vector<sharedPtr<SMeshBuffer>>::iterator bit = MeshBuffers.begin(); bit != MeshBuffers.end(); ++ bit)
		for (std::vector<SVertex>::iterator it = (* bit)->Vertices.begin(); it != (* bit)->Vertices.end(); ++ it)
		{
			SVector3f const RelativePosition = (it->Position - Min) / (Max - Min);
			it->TextureCoordinates = vec2f((RelativePosition * uVec.GetNormalized()).Length(),
				(RelativePosition * vVec.GetNormalized()).Length()) * Scale;
		}
}

void CMesh::UpdateBuffers()
{
	for (std::vector<sharedPtr<SMeshBuffer>>::iterator bit = MeshBuffers.begin(); bit != MeshBuffers.end(); ++ bit)
		(* bit)->UpdateBuffers();
}
