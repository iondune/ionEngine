
#pragma once

#include <ionCore.h>
#include <ionMath.h>
#include <ionGL.h>

#include "SVertex.h"
#include "SMeshTriangle.h"
#include "SMaterial.h"


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

	vector<SVertex> Vertices;
	vector<SMeshTriangle> Triangles;

	//! \brief Pointer to the Material of this buffer.
	//! Assumed an element of the containing CMesh
	//! Buffer and Material duration should be equivalent,
	//! so this pointer is assumed valid.
	//! It is up to the CMesh to ensure validity.
	SMaterial * Material;

	struct SVertexBuffers
	{
		ion::GL::VertexBuffer * Positions, * Normals, * Colors, * TexCoords;
		ion::GL::IndexBuffer * Indices;
	} VertexBuffers;
	ion::GL::VertexArray * ArrayObject;

};
