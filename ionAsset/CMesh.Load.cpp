
#include "CMesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


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
		sharedPtr<CMesh::SMeshBuffer> Buffer = sharedNew(new CMesh::SMeshBuffer);

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
			SMeshTriangle Triangle;
			for (uint k = 0; k < 3; ++ k)
				Triangle.Indices[k] = Mesh->mFaces[j].mIndices[k];

			Buffer->Triangles.push_back(Triangle);
		}

		aiMaterial * Material = Scene->mMaterials[Mesh->mMaterialIndex];
		aiColor4D Color;
		Material->Get(AI_MATKEY_COLOR_DIFFUSE, Color);
		Buffer->Material.Diffuse = color4f(Color.r, Color.g, Color.b, Color.a);
		Material->Get(AI_MATKEY_COLOR_AMBIENT, Color);
		Buffer->Material.Ambient = color4f(Color.r, Color.g, Color.b, Color.a);
		Material->Get(AI_MATKEY_COLOR_SPECULAR, Color);
		Buffer->Material.Specular = color4f(Color.r, Color.g, Color.b, Color.a);

		Result->MeshBuffers.push_back(Buffer);
	}

	for (uint i = 0; i < Node->mNumChildren; ++ i)
		TraverseMesh(Result, Scene, Node->mChildren[i], Transformation);

	return Result;
}

CMesh * CMesh::Load(std::string const & FileName)
{
	Assimp::Importer Importer;

	aiScene const * const Scene = Importer.ReadFile(FileName,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType
	);

	if (! Scene)
	{
		std::cerr << "Failed to import mesh file '" << FileName << "': " << Importer.GetErrorString() << std::endl;
		return 0;
	}

	CMesh * Result = new CMesh;
	TraverseMesh(Result, Scene, Scene->mRootNode, glm::mat4(1));
	return Result;
}
