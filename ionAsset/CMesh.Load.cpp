
#include "CMesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


SMaterial * LoadMaterial(aiMaterial * Material);
SMeshBuffer * LoadBuffer(aiMesh * Mesh, vector<SMaterial *> const & Materials);
SMeshNode * TraverseMesh(aiScene const * Scene, aiNode * Node, vector<SMeshBuffer *> const & Buffers);


CMesh * CMesh::Load(std::string const & FileName)
{
	Assimp::Importer Importer;

	aiScene const * const Scene = Importer.ReadFile(FileName,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType |
		aiProcess_GenNormals
		);

	if (! Scene)
	{
		std::cerr << "Failed to import mesh file '" << FileName << "': " << Importer.GetErrorString() << std::endl;
		return 0;
	}

	CMesh * Result = new CMesh{};

	for (uint i = 0; i < Scene->mNumMaterials; ++ i)
		Result->Materials.push_back(LoadMaterial(Scene->mMaterials[i]));

	for (uint i = 0; i < Scene->mNumMeshes; ++ i)
		Result->Buffers.push_back(LoadBuffer(Scene->mMeshes[i], Result->Materials));

	Result->Root = TraverseMesh(Scene, Scene->mRootNode, Result->Buffers);
	Result->Update();

	return Result;
}


SMaterial * LoadMaterial(aiMaterial * Material)
{
	SMaterial * Result = new SMaterial{};
	aiColor4D Color;

	Material->Get(AI_MATKEY_COLOR_DIFFUSE, Color);
	Result->Diffuse = color4f(Color.r, Color.g, Color.b, Color.a);
	Material->Get(AI_MATKEY_COLOR_AMBIENT, Color);
	Result->Ambient = color4f(Color.r, Color.g, Color.b, Color.a);
	Material->Get(AI_MATKEY_COLOR_SPECULAR, Color);
	Result->Specular = color4f(Color.r, Color.g, Color.b, Color.a);

	return Result;
}

SMeshBuffer * LoadBuffer(aiMesh * Mesh, vector<SMaterial *> const & Materials)
{
	SMeshBuffer * Buffer = new SMeshBuffer{};

	// Vertices
	Buffer->Vertices.reserve(Mesh->mNumVertices);
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

		Buffer->Vertices.push_back(Vertex);
	}

	// Faces
	Buffer->Triangles.reserve(Mesh->mNumFaces);
	for (uint j = 0; j < Mesh->mNumFaces; ++ j)
	{
		SMeshTriangle Triangle;
		for (uint k = 0; k < 3; ++ k)
			Triangle.Indices[k] = Mesh->mFaces[j].mIndices[k];

		Buffer->Triangles.push_back(Triangle);
	}

	// Material
	Buffer->Material = Materials[Mesh->mMaterialIndex];

	return Buffer;
}

SMeshNode * TraverseMesh(aiScene const * Scene, aiNode * Node, vector<SMeshBuffer *> const & Buffers)
{
	SMeshNode * Result = new SMeshNode{};

	Result->Transformation = glm::mat4(
		Node->mTransformation.a1, Node->mTransformation.b1, Node->mTransformation.c1, Node->mTransformation.d1,
		Node->mTransformation.a2, Node->mTransformation.b2, Node->mTransformation.c2, Node->mTransformation.d2,
		Node->mTransformation.a3, Node->mTransformation.b3, Node->mTransformation.c3, Node->mTransformation.d3,
		Node->mTransformation.a4, Node->mTransformation.b4, Node->mTransformation.c4, Node->mTransformation.d4
		);

	for (uint i = 0; i < Node->mNumMeshes; ++ i)
		Result->Buffers.push_back(Buffers[Node->mMeshes[i]]);

	for (uint i = 0; i < Node->mNumChildren; ++ i)
		Result->AddChild(TraverseMesh(Scene, Node->mChildren[i], Buffers));

	return Result;
}
