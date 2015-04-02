
#pragma once

#include <ionCore.h>
#include <ionMath.h>
#include <ionGL.h>

#include "SVertex.h"
#include "SMeshTriangle.h"
#include "SMaterial.h"


struct SMeshBone
{

	glm::mat4 OffsetMatrix, RelativeTransform;
	string Name;
	SMeshBone * Parent = nullptr;

};

struct SMeshBuffer
{

	SMeshBuffer();
	SMeshBuffer(vector<uint> Indices,
		vector<f32> const & Positions,
		vector<f32> const & Normals = vector<f32>(),
		vector<f32> const & Colors = vector<f32>(),
		vector<f32> const & TexCoords = vector<f32>());

	void LoadDataIntoBuffers();
	void WriteObjMesh(std::string const & FileName);

	SMaterial * GetMaterial();

	vector<SVertex> Vertices;
	vector<SMeshTriangle> Triangles;
	vector<SMeshBone> Bones;

	//! \brief Pointer to the Material of this buffer.
	//! Assumed an element of the containing CMesh
	//! Buffer and Material duration should be equivalent,
	//! so this pointer is assumed valid.
	//! It is up to the CMesh to ensure validity.
	SMaterial * Material = 0;

	struct SVertexBuffers
	{
		ion::GL::VertexBuffer * Positions = 0, * Normals = 0, * Colors = 0, * TexCoords = 0, * BoneWeights = 0, * BoneIndices = 0;
		ion::GL::IndexBuffer * Indices = 0;
	} VertexBuffers;

};
