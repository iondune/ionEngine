
#include "CMeshLoader.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


std::string CMeshLoader::MeshDirectory = "../Media/Models/";

CMesh * TraverseMesh(CMesh * Result, aiScene const * Scene, aiNode * Node, glm::mat4 Transformation)
{
	glm::mat4 LocalTransformation = glm::mat4(
		Node->mTransformation.a1, Node->mTransformation.b1, Node->mTransformation.c1, Node->mTransformation.d1,
		Node->mTransformation.a2, Node->mTransformation.b2, Node->mTransformation.c2, Node->mTransformation.d2,
		Node->mTransformation.a3, Node->mTransformation.b3, Node->mTransformation.c3, Node->mTransformation.d3,
		Node->mTransformation.a4, Node->mTransformation.b4, Node->mTransformation.c4, Node->mTransformation.d4
		);
	Transformation = Transformation * LocalTransformation;

	for (uint i = 0; i < Node->mNumMeshes; ++ i)
	{
		aiMesh * Mesh = Scene->mMeshes[Node->mMeshes[i]];
		CMesh::SMeshBuffer * Buffer = new CMesh::SMeshBuffer;

		for (uint j = 0; j < Mesh->mNumVertices; ++ j)
		{
			SVertex Vertex;
			Vertex.Position = vec3f(Mesh->mVertices[j].x, Mesh->mVertices[j].y, Mesh->mVertices[j].z);
			if (Mesh->HasNormals())
				Vertex.Normal = vec3f(Mesh->mNormals[j].x, Mesh->mNormals[j].y, Mesh->mNormals[j].z);
			if (Mesh->HasTextureCoords(0))
				Vertex.TextureCoordinates = vec2f(Mesh->mTextureCoords[0][j].x, Mesh->mTextureCoords[0][j].y);
			if (Mesh->HasVertexColors(0))
				Vertex.Color = color4f(Mesh->mColors[0][j].r, Mesh->mColors[0][j].g, Mesh->mColors[0][j].b, Mesh->mColors[0][j].a);

			glm::vec4 Pos = glm::vec4(Vertex.Position.X, Vertex.Position.Y, Vertex.Position.Z, 1);
			Pos = Transformation * Pos;
			Vertex.Position = vec3f(Pos.x, Pos.y, Pos.z);

			Buffer->Vertices.push_back(Vertex);
		}
		for (uint j = 0; j < Mesh->mNumFaces; ++ j)
		{
			CMesh::STriangle Triangle;
			for (uint k = 0; k < 3; ++ k)
				Triangle.Indices[k] = Mesh->mFaces[j].mIndices[k];

			Buffer->Triangles.push_back(Triangle);
		}

		Result->MeshBuffers.push_back(Buffer);
	}

	for (uint i = 0; i < Node->mNumChildren; ++ i)
		TraverseMesh(Result, Scene, Node->mChildren[i], Transformation);

	return Result;
}

CMesh * const CMeshLoader::LoadMesh(std::string const & FileName)
{
	Assimp::Importer Importer;

	aiScene const * const Scene = Importer.ReadFile(MeshDirectory + FileName,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType
	);

	if (! Scene)
	{
		std::cerr << "Failed to import mesh file '" << MeshDirectory + FileName << "': " << Importer.GetErrorString() << std::endl;
		return 0;
	}

	CMesh * Result = new CMesh;
	TraverseMesh(Result, Scene, Scene->mRootNode, glm::mat4(1));
	return Result;
}

CMesh * const CMeshLoader::CreateCubeMesh()
{
	Assimp::Importer importer;
    CMesh * MeshWrapper = new CMesh();
    CMesh::SMeshBuffer * Mesh = new CMesh::SMeshBuffer();

    Mesh->Vertices.resize(24);
    Mesh->Vertices[0].Position = SVector3f(-0.5, -0.5, -0.5);
    Mesh->Vertices[1].Position = SVector3f(-0.5,  0.5, -0.5);
    Mesh->Vertices[2].Position = SVector3f( 0.5,  0.5, -0.5);
    Mesh->Vertices[3].Position = SVector3f( 0.5, -0.5, -0.5);

    Mesh->Vertices[4].Position = SVector3f( 0.5, -0.5, -0.5);
    Mesh->Vertices[5].Position = SVector3f( 0.5, 0.5, -0.5);
    Mesh->Vertices[6].Position = SVector3f( 0.5, 0.5,  0.5);
    Mesh->Vertices[7].Position = SVector3f( 0.5, -0.5,  0.5);

    Mesh->Vertices[8].Position = SVector3f( 0.5, -0.5,  0.5);
    Mesh->Vertices[9].Position = SVector3f( 0.5,  0.5,  0.5);
    Mesh->Vertices[10].Position = SVector3f(-0.5,  0.5,  0.5);
    Mesh->Vertices[11].Position = SVector3f(-0.5, -0.5,  0.5);

    Mesh->Vertices[12].Position = SVector3f(-0.5, -0.5,  0.5);
    Mesh->Vertices[13].Position = SVector3f(-0.5,  0.5,  0.5);
    Mesh->Vertices[14].Position = SVector3f(-0.5,  0.5, -0.5);
    Mesh->Vertices[15].Position = SVector3f(-0.5, -0.5, -0.5);

    Mesh->Vertices[16].Position = SVector3f(-0.5,  0.5, -0.5);
    Mesh->Vertices[17].Position = SVector3f(-0.5,  0.5,  0.5);
    Mesh->Vertices[18].Position = SVector3f( 0.5,  0.5,  0.5);
    Mesh->Vertices[19].Position = SVector3f( 0.5,  0.5, -0.5);

    Mesh->Vertices[20].Position = SVector3f( 0.5, -0.5, -0.5);
    Mesh->Vertices[21].Position = SVector3f( 0.5, -0.5,  0.5);
    Mesh->Vertices[22].Position = SVector3f(-0.5, -0.5,  0.5);
    Mesh->Vertices[23].Position = SVector3f(-0.5, -0.5, -0.5);

    Mesh->Triangles.resize(12);
    for (int i = 0; i < 6; ++ i)
    {
        Mesh->Vertices[4*i + 0].TextureCoordinates = SVector2f(0, 1);
        Mesh->Vertices[4*i + 1].TextureCoordinates = SVector2f(0, 0);
        Mesh->Vertices[4*i + 2].TextureCoordinates = SVector2f(1, 0);
        Mesh->Vertices[4*i + 3].TextureCoordinates = SVector2f(1, 1);

        Mesh->Triangles[2*i].Indices[0] = 4*i + 0;
        Mesh->Triangles[2*i].Indices[1] = 4*i + 1;
        Mesh->Triangles[2*i].Indices[2] = 4*i + 2;

        Mesh->Triangles[2*i+1].Indices[0] = 4*i + 0;
        Mesh->Triangles[2*i+1].Indices[1] = 4*i + 2;
        Mesh->Triangles[2*i+1].Indices[2] = 4*i + 3;
    }

    MeshWrapper->MeshBuffers.push_back(Mesh);

    MeshWrapper->calculateNormalsPerFace();
    return MeshWrapper;
}

CMesh * const CMeshLoader::CreatePlaneMesh()
{
    CMesh * MeshWrapper = new CMesh();
    CMesh::SMeshBuffer * Mesh = new CMesh::SMeshBuffer();

    Mesh->Vertices.resize(4);
    Mesh->Vertices[0].Position = SVector3f(-0.5, 0, -0.5);
    Mesh->Vertices[1].Position = SVector3f(-0.5, 0,  0.5);
    Mesh->Vertices[2].Position = SVector3f( 0.5, 0,  0.5);
    Mesh->Vertices[3].Position = SVector3f( 0.5, 0, -0.5);

    Mesh->Vertices[0].TextureCoordinates = SVector2f(0, 1);
    Mesh->Vertices[1].TextureCoordinates = SVector2f(0, 0);
    Mesh->Vertices[2].TextureCoordinates = SVector2f(1, 0);
    Mesh->Vertices[3].TextureCoordinates = SVector2f(1, 1);
	
    Mesh->Triangles.resize(2);
    Mesh->Triangles[0].Indices[0] = 0;
    Mesh->Triangles[0].Indices[1] = 1;
    Mesh->Triangles[0].Indices[2] = 2;

    Mesh->Triangles[1].Indices[0] = 0;
    Mesh->Triangles[1].Indices[1] = 2;
    Mesh->Triangles[1].Indices[2] = 3;

    MeshWrapper->MeshBuffers.push_back(Mesh);
    MeshWrapper->calculateNormalsPerFace();
    return MeshWrapper;
}

CMesh * const CMeshLoader::CreateDiscMesh(unsigned int const Triangles)
{
    CMesh * MeshWrapper = new CMesh();
    CMesh::SMeshBuffer * Mesh = new CMesh::SMeshBuffer();

    Mesh->Vertices.resize(Triangles * 3);
    Mesh->Triangles.resize(Triangles);

    for (unsigned int i = 0; i < Triangles; ++ i)
    {
        Mesh->Vertices[i*3 + 0].Position.X = 0;
        Mesh->Vertices[i*3 + 0].Position.Y = 0;
        Mesh->Vertices[i*3 + 0].Position.Z = 0;

        Mesh->Vertices[i*3 + 1].Position.X = 0.5f * sin(float(i) / float(Triangles) * 2.f * 3.14159f);
        Mesh->Vertices[i*3 + 1].Position.Y = 0;
        Mesh->Vertices[i*3 + 1].Position.Z = 0.5f * cos(float(i) / float(Triangles) * 2.f * 3.14159f);

        Mesh->Vertices[i*3 + 2].Position.X = 0.5f * sin(float(i+1) / float(Triangles) * 2.f * 3.14159f);
        Mesh->Vertices[i*3 + 2].Position.Y = 0;
        Mesh->Vertices[i*3 + 2].Position.Z = 0.5f * cos(float(i+1) / float(Triangles) * 2.f * 3.14159f);

		Mesh->Vertices[i*3 + 0].Normal = SVector3f(0, 0, 1);
		Mesh->Vertices[i*3 + 1].Normal = SVector3f(0, 0, 1);
		Mesh->Vertices[i*3 + 2].Normal = SVector3f(0, 0, 1);

        Mesh->Triangles[i].Indices[0] = i*3 + 0;
        Mesh->Triangles[i].Indices[1] = i*3 + 1;
        Mesh->Triangles[i].Indices[2] = i*3 + 2;
    }

    for (unsigned int i = 0; i < Mesh->Vertices.size(); ++ i)
    {
        Mesh->Vertices[i].TextureCoordinates = SVector2f(Mesh->Vertices[i].Position.X, Mesh->Vertices[i].Position.Y) + SVector2f(0.5f);
    }

    MeshWrapper->MeshBuffers.push_back(Mesh);

    MeshWrapper->calculateNormalsPerFace();
    return MeshWrapper;
}
