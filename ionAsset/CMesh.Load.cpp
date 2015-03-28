
#include "CMesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


SMaterial * LoadMaterial(aiMaterial * Material);
SMeshBuffer * LoadBuffer(aiNode * RootNode, aiMesh * Mesh, vector<SMaterial *> const & Materials);
SMeshNode * TraverseMesh(aiScene const * Scene, aiNode * Node, vector<SMeshBuffer *> const & Buffers);


CMesh * CMesh::Load(std::string const & FileName)
{
	Assimp::Importer Importer;

	unsigned int pFlags = 
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType |
		aiProcess_GenNormals;

	aiScene const * const Scene = Importer.ReadFile(FileName, pFlags);

	if (! Scene)
	{
		std::cerr << "Failed to import mesh file '" << FileName << "': " << Importer.GetErrorString() << std::endl;
		return 0;
	}

	CMesh * Result = new CMesh{};

	for (uint i = 0; i < Scene->mNumMaterials; ++ i)
		Result->Materials.push_back(LoadMaterial(Scene->mMaterials[i]));

	for (uint i = 0; i < Scene->mNumMeshes; ++ i)
		Result->Buffers.push_back(LoadBuffer(Scene->mRootNode, Scene->mMeshes[i], Result->Materials));

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

glm::mat4 AItoGLM(aiMatrix4x4 const & ai)
{
	return glm::mat4(
		ai.a1, ai.b1, ai.c1, ai.d1,
		ai.a2, ai.b2, ai.c2, ai.d2,
		ai.a3, ai.b3, ai.c3, ai.d3,
		ai.a4, ai.b4, ai.c4, ai.d4
		);
}

string FindParentName(string const & ChildName, aiNode * Node)
{
	for (int i = 0; i < Node->mNumChildren; ++ i)
	{
		if (ChildName == Node->mChildren[i]->mName.C_Str())
			return Node->mName.C_Str();
		else
		{
			string Name = FindParentName(ChildName, Node->mChildren[i]);
			if (Name.size())
				return Name;
		}
	}

	return "";
}

SMeshBuffer * LoadBuffer(aiNode * RootNode, aiMesh * Mesh, vector<SMaterial *> const & Materials)
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

	// Bones
	for (uint j = 0; j < Mesh->mNumBones; ++ j)
	{
		SMeshBone Bone;
		Bone.Name = Mesh->mBones[j]->mName.C_Str();
		Bone.Matrix = AItoGLM(Mesh->mBones[j]->mOffsetMatrix);

		for (uint k = 0; k < Mesh->mBones[j]->mNumWeights; ++ k)
		{
			if (Buffer->Vertices[Mesh->mBones[j]->mWeights[k].mVertexId].BoneIndices[0] == -1)
			{
				Buffer->Vertices[Mesh->mBones[j]->mWeights[k].mVertexId].BoneIndices[0] = j;
				Buffer->Vertices[Mesh->mBones[j]->mWeights[k].mVertexId].BoneWeights[0] = Mesh->mBones[j]->mWeights[k].mWeight;
			}
			else if (Buffer->Vertices[Mesh->mBones[j]->mWeights[k].mVertexId].BoneIndices[1] == -1)
			{
				Buffer->Vertices[Mesh->mBones[j]->mWeights[k].mVertexId].BoneIndices[1] = j;
				Buffer->Vertices[Mesh->mBones[j]->mWeights[k].mVertexId].BoneWeights[1] = Mesh->mBones[j]->mWeights[k].mWeight;
			}
			else
			{
				printf("Error! Vertex in mesh has more than two bone weights!\n");
			}
		}

		Buffer->Bones.push_back(Bone);
	}

	for (auto Bone : Buffer->Bones)
	{
		string const ParentName = FindParentName(Bone.Name, RootNode);
		for (auto & Parent : Buffer->Bones)
		{
			if (ParentName == Parent.Name)
				Bone.Parent = & Parent;
		}
	}

	// Material
	Buffer->Material = Materials[Mesh->mMaterialIndex];

	return Buffer;
}

SMeshNode * TraverseMesh(aiScene const * Scene, aiNode * Node, vector<SMeshBuffer *> const & Buffers)
{
	SMeshNode * Result = new SMeshNode{};

	Result->Transformation = AItoGLM(Node->mTransformation);

	for (uint i = 0; i < Node->mNumMeshes; ++ i)
		Result->Buffers.push_back(Buffers[Node->mMeshes[i]]);

	for (uint i = 0; i < Node->mNumChildren; ++ i)
		Result->AddChild(TraverseMesh(Scene, Node->mChildren[i], Buffers));

	return Result;
}
