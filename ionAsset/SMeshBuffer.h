
#pragma once

#include <ionCore.h>
#include <ionMath.h>
#include <ionGL.h>

#include "SVertex.h"
#include "SMeshTriangle.h"
#include "SMaterial.h"


struct SMeshBuffer
{
	std::vector<SVertex> Vertices;
	std::vector<SMeshTriangle> Triangles;

	// struct SVertexBuffers
	// {
	ion::GL::VertexBuffer * Positions, * Normals, * Colors, * TexCoords;
	ion::GL::IndexBuffer * Indices;
	// } VertexBuffers;
	ion::GL::VertexArray * ArrayObject;

	SMeshBuffer();
	SMeshBuffer(vector<uint> Indices,
		vector<f32> const & Positions,
		vector<f32> const & Normals = vector<f32>(),
		vector<f32> const & Colors = vector<f32>(),
		vector<f32> const & TexCoords = vector<f32>());

	void LoadDataIntoBuffers();
	void WriteObjMesh(std::string const & FileName);

	SMaterial Material;
	glm::mat4 Transformation;
};
