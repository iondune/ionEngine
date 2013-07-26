#include "CMesh.h"

#include <limits>
#include <fstream>

void CMesh::SMeshBuffer::updateBuffers()
{
	PositionBuffer.clear();
	ColorBuffer.clear();
	NormalBuffer.clear();
	TexCoordBuffer.clear();
	IndexBuffer.clear();
	NormalLineBuffer.clear();
	NormalColorBuffer.clear();
	NormalIndexBuffer.clear();

	for (std::vector<SVertex>::iterator it = Vertices.begin(); it != Vertices.end(); ++ it)
		for (unsigned int j = 0; j < 3; ++ j)
			PositionBuffer.push_back(it->Position[j]);

	for (std::vector<SVertex>::iterator it = Vertices.begin(); it != Vertices.end(); ++ it)
		for (unsigned int j = 0; j < 3; ++ j)
			ColorBuffer.push_back(it->Color[j]);

	for (std::vector<SVertex>::iterator it = Vertices.begin(); it != Vertices.end(); ++ it)
		for (unsigned int j = 0; j < 3; ++ j)
			NormalBuffer.push_back(it->Normal[j]);

	for (std::vector<SVertex>::iterator it = Vertices.begin(); it != Vertices.end(); ++ it)
		for (unsigned int j = 0; j < 2; ++ j)
			TexCoordBuffer.push_back(it->TextureCoordinates[j]);

	for (std::vector<STriangle>::iterator it = Triangles.begin(); it != Triangles.end(); ++ it)
		for (unsigned int j = 0; j < 3; ++ j)
			IndexBuffer.push_back((* it).Indices[j]);

	IndexBuffer.setIsIndexBuffer(true);


	static float const LengthFactor = 0.05f;

	for (std::vector<SVertex>::iterator it = Vertices.begin(); it != Vertices.end(); ++ it)
	{
		for (unsigned int j = 0; j < 3; ++ j)
			NormalLineBuffer.push_back(it->Position[j]);
		for (unsigned int j = 0; j < 3; ++ j)
			NormalLineBuffer.push_back(it->Position[j] + it->Normal[j]*LengthFactor);
	}

	for (std::vector<SVertex>::iterator it = Vertices.begin(); it != Vertices.end(); ++ it)
	{
		for (unsigned int j = 0; j < 3; ++ j)
			NormalColorBuffer.push_back(it->Color[j]);
		for (unsigned int j = 0; j < 3; ++ j)
			NormalColorBuffer.push_back(it->Color[j]);
	}

	for (unsigned int i = 0; i < Vertices.size(); ++ i)
		for (unsigned int j = 0; j < 2; ++ j)
			NormalIndexBuffer.push_back(i*2 + j);

	NormalIndexBuffer.setIsIndexBuffer(true);
}

void CMesh::SMeshBuffer::writeObjMesh(std::string const & fileName)
{
	std::ofstream File(fileName);

	File << "#vertices" << std::endl;
	for (std::vector<SVertex>::iterator it = Vertices.begin(); it != Vertices.end(); ++ it)
		File << "v " << it->Position.X << " " << it->Position.Y << " " << it->Position.Z << std::endl;

	File << "#normals" << std::endl;
	for (std::vector<SVertex>::iterator it = Vertices.begin(); it != Vertices.end(); ++ it)
		File << "vn " << it->Normal.X << " " << it->Normal.Y << " " << it->Normal.Z << std::endl;
	
	File << std::endl << "#faces" << std::endl;
	for (std::vector<STriangle>::iterator it = Triangles.begin(); it != Triangles.end(); ++ it)
		File << "f " << 
			it->Indices[0] + 1 << "//" << it->Indices[0] + 1 << " " << 
			it->Indices[1] + 1 << "//" << it->Indices[1] + 1 << " " << 
			it->Indices[2] + 1 << "//" << it->Indices[2] + 1 << std::endl;

	File.close();
}

CMesh::CMesh()
	: Dirty(true), Revision(0)
{}

CMesh::~CMesh()
{
	for (std::vector<SMeshBuffer *>::const_iterator bit = MeshBuffers.begin(); bit != MeshBuffers.end(); ++ bit)
		delete *bit;
}

unsigned int const CMesh::getVertexCount() const
{
	unsigned int Count = 0;
	for (std::vector<SMeshBuffer *>::const_iterator bit = MeshBuffers.begin(); bit != MeshBuffers.end(); ++ bit)
		Count += (* bit)->Vertices.size();
	return Count;
}

void CMesh::centerMeshByAverage(SVector3f const & CenterLocation)
{
	SVector3f VertexSum;
	for (std::vector<SMeshBuffer *>::const_iterator bit = MeshBuffers.begin(); bit != MeshBuffers.end(); ++ bit)
		for (std::vector<SVertex>::const_iterator it = (* bit)->Vertices.begin(); it != (* bit)->Vertices.end(); ++ it)
			VertexSum += it->Position;

	VertexSum /= (float) getVertexCount();
	SVector3f VertexOffset = CenterLocation - VertexSum;
	for (std::vector<SMeshBuffer *>::iterator bit = MeshBuffers.begin(); bit != MeshBuffers.end(); ++ bit)
		for (std::vector<SVertex>::iterator it = (* bit)->Vertices.begin(); it != (* bit)->Vertices.end(); ++ it)
			it->Position += VertexOffset;
}

void CMesh::centerMeshByExtents(SVector3f const & CenterLocation)
{
	SVector3f Min(std::numeric_limits<float>::max()), Max(-std::numeric_limits<float>::max());
	{
		for (std::vector<SMeshBuffer *>::const_iterator bit = MeshBuffers.begin(); bit != MeshBuffers.end(); ++ bit)
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
	for (std::vector<SMeshBuffer *>::iterator bit = MeshBuffers.begin(); bit != MeshBuffers.end(); ++ bit)
		for (std::vector<SVertex>::iterator it = (* bit)->Vertices.begin(); it != (* bit)->Vertices.end(); ++ it)
			it->Position += VertexOffset;
}

void CMesh::resizeMesh(SVector3f const & Scale)
{
	SVector3f Extent = getExtent();
	SVector3f Resize = Scale / std::max(Extent.X, std::max(Extent.Y, Extent.Z));
	for (std::vector<SMeshBuffer *>::iterator bit = MeshBuffers.begin(); bit != MeshBuffers.end(); ++ bit)
		for (std::vector<SVertex>::iterator it = (* bit)->Vertices.begin(); it != (* bit)->Vertices.end(); ++ it)
			it->Position *= Resize;
}

SVector3f const CMesh::getExtent() const
{
	SVector3f Min(std::numeric_limits<float>::max()), Max(-std::numeric_limits<float>::max());
	{
		for (std::vector<SMeshBuffer *>::const_iterator bit = MeshBuffers.begin(); bit != MeshBuffers.end(); ++ bit)
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

void CMesh::calculateNormalsPerFace()
{
	for (std::vector<SMeshBuffer *>::iterator bit = MeshBuffers.begin(); bit != MeshBuffers.end(); ++ bit)
	{
		for (std::vector<STriangle>::iterator it = (* bit)->Triangles.begin(); it != (* bit)->Triangles.end(); ++ it)
		{
			it->Normal = ((* bit)->Vertices[it->Indices[1]].Position - (* bit)->Vertices[it->Indices[0]].Position).
				CrossProduct((* bit)->Vertices[it->Indices[2]].Position - (* bit)->Vertices[it->Indices[0]].Position);
			(* bit)->Vertices[it->Indices[0]].Normal = (* bit)->Vertices[it->Indices[1]].Normal = (* bit)->Vertices[it->Indices[2]].Normal = it->Normal;
		}
	}

	for (std::vector<SMeshBuffer *>::iterator bit = MeshBuffers.begin(); bit != MeshBuffers.end(); ++ bit)
		for (std::vector<SVertex>::iterator it = (* bit)->Vertices.begin(); it != (* bit)->Vertices.end(); ++ it) {
			it->Normal.Normalize();
		}
}

void CMesh::reverseFaces()
{
	for (std::vector<SMeshBuffer *>::iterator bit = MeshBuffers.begin(); bit != MeshBuffers.end(); ++ bit)
	{
		for (std::vector<STriangle>::iterator it = (* bit)->Triangles.begin(); it != (* bit)->Triangles.end(); ++ it)
		{
			u32 temp = it->Indices[1];
			it->Indices[1] = it->Indices[2];
			it->Indices[2] = temp;
		}
	}
}

void CMesh::calculateNormalsPerVertex(bool CombineNear, float const NearTolerance)
{
	calculateNormalsPerFace();

	for (std::vector<SMeshBuffer *>::iterator bit = MeshBuffers.begin(); bit != MeshBuffers.end(); ++ bit)
		for (std::vector<SVertex>::iterator it = (* bit)->Vertices.begin(); it != (* bit)->Vertices.end(); ++ it)
			it->Normal = SVector3f();

	for (std::vector<SMeshBuffer *>::iterator bit = MeshBuffers.begin(); bit != MeshBuffers.end(); ++ bit)
		for (std::vector<STriangle>::iterator it = (* bit)->Triangles.begin(); it != (* bit)->Triangles.end(); ++ it)
			for (int i = 0; i < 3; ++ i)
				(* bit)->Vertices[it->Indices[i]].Normal += it->Normal;

	if (CombineNear)
		for (std::vector<SMeshBuffer *>::iterator bit = MeshBuffers.begin(); bit != MeshBuffers.end(); ++ bit)
			for (unsigned int i = 0; i < (* bit)->Vertices.size(); ++ i)
				for (unsigned int j = i + 1; j < (* bit)->Vertices.size(); ++ j)
					if ((* bit)->Vertices[i].Position.Equals((* bit)->Vertices[j].Position, NearTolerance))
						(* bit)->Vertices[i].Normal = (* bit)->Vertices[j].Normal = (* bit)->Vertices[i].Normal + (* bit)->Vertices[j].Normal;


	for (std::vector<SMeshBuffer *>::iterator bit = MeshBuffers.begin(); bit != MeshBuffers.end(); ++ bit)
		for (std::vector<SVertex>::iterator it = (* bit)->Vertices.begin(); it != (* bit)->Vertices.end(); ++ it)
			it->Normal.Normalize();
}


void CMesh::calculateTextureCoordinates(vec3f const & uVec, vec3f const & vVec, vec2f const & Scale)
{
	SVector3f Min(std::numeric_limits<float>::max()), Max(-std::numeric_limits<float>::max());
	{
		for (std::vector<SMeshBuffer *>::const_iterator bit = MeshBuffers.begin(); bit != MeshBuffers.end(); ++ bit)
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

	for (std::vector<SMeshBuffer *>::iterator bit = MeshBuffers.begin(); bit != MeshBuffers.end(); ++ bit)
		for (std::vector<SVertex>::iterator it = (* bit)->Vertices.begin(); it != (* bit)->Vertices.end(); ++ it)
		{
			SVector3f const RelativePosition = (it->Position - Min) / (Max - Min);
			it->TextureCoordinates = vec2f((RelativePosition * uVec.GetNormalized()).Length(),
				(RelativePosition * vVec.GetNormalized()).Length()) * Scale;
		}
}

void CMesh::updateBuffers()
{
	for (std::vector<SMeshBuffer *>::iterator bit = MeshBuffers.begin(); bit != MeshBuffers.end(); ++ bit)
		(* bit)->updateBuffers();

	++ Revision;
	Dirty = false;
}

SBoundingBox3f const CMesh::getBoundingBox() const
{
	SBoundingBox3f Box(SVector3f(std::numeric_limits<float>().max()), SVector3f(-std::numeric_limits<float>().max()));

	for (std::vector<SMeshBuffer *>::const_iterator bit = MeshBuffers.begin(); bit != MeshBuffers.end(); ++ bit)
		for (std::vector<SVertex>::const_iterator it = (* bit)->Vertices.begin(); it != (* bit)->Vertices.end(); ++ it)
			Box.AddInternalPoint(it->Position);

	return Box;
}

void CMesh::linearizeIndices()
{
	for (std::vector<SMeshBuffer *>::iterator bit = MeshBuffers.begin(); bit != MeshBuffers.end(); ++ bit)
	{
		std::vector<SVertex> newVertices;
		std::vector<STriangle> newTriangles;

		for (std::vector<STriangle>::iterator it = (* bit)->Triangles.begin(); it != (* bit)->Triangles.end(); ++ it)
		{
			for (int i = 0; i < 3; ++ i)
				newVertices.push_back((* bit)->Vertices[it->Indices[i]]);
		}

		for (unsigned int i = 0; i < newVertices.size()/3; ++ i)
		{
			STriangle tri;
			tri.Indices[0] = i*3;
			tri.Indices[1] = i*3 + 1;
			tri.Indices[2] = i*3 + 2;
			newTriangles.push_back(tri);
		}

		(* bit)->Vertices = newVertices;
		(* bit)->Triangles = newTriangles;
	}
}

bool const CMesh::isDirty() const
{
	return Dirty;
}

void CMesh::setDirty(bool const dirty)
{
	Dirty = dirty;
}

unsigned int const CMesh::getRevision() const
{
	return Revision;
}
