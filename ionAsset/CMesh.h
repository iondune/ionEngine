
#pragma once

#include <ionMath/SBoundingBox3.h>
#include <ionGraphics/CBufferObject.h>

#include "SVertex.h"
#include "SMeshTriangle.h"
#include "SMaterial.h"


class CMesh
{

public:

    struct SMeshBuffer
    {
        std::vector<SVertex> Vertices;
        std::vector<SMeshTriangle> Triangles;

		CBufferObject<f32> Positions, Colors, Normals, TexCoords;
		CBufferObject<uint> Indices;

		void UpdateBuffers();
		void WriteObjMesh(std::string const & FileName);

		SMaterial Material;
    };

    std::vector<sharedPtr<SMeshBuffer>> MeshBuffers;

	static CMesh * Load(std::string const & FileName);

	uint GetVertexCount() const;
	SBoundingBox3f GetBoundingBox() const;
	vec3f GetExtent() const;

    void CenterMeshByAverage(vec3f const & CenterLocation);
    void CenterMeshByExtents(vec3f const & CenterLocation);
    void ResizeMesh(vec3f const & Scale);
	void ReverseFaces();
	void LinearizeIndices();

    void CalculateNormalsPerFace();
    void CalculateNormalsPerVertex(bool CombineNear = true, f32 const NearTolerance = 0.01f);
	void CalculateTextureCoordinates(vec3f const & uVec, vec3f const & vVec, vec2f const & Scale = vec2f(1.f));

    void UpdateBuffers();

};
