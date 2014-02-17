
#pragma once

#include <ionMath/SBoundingBox3.h>
#include <ionGraphics/CBufferObject.h>
#include <ionGraphics/CRenderable.h>

#include "SVertex.h"


class CMesh
{

	bool Dirty;
	uint Revision;

public:

    struct STriangle
    {
        uint Indices[3];
        vec3f Normal;
    };

    struct SMeshBuffer
    {
        std::vector<SVertex> Vertices;
        std::vector<STriangle> Triangles;

		CBufferObject<float> PositionBuffer, ColorBuffer, NormalBuffer, TexCoordBuffer, NormalLineBuffer, NormalColorBuffer;
		CBufferObject<uint> IndexBuffer, NormalIndexBuffer;

		void updateBuffers();
		void writeObjMesh(std::string const & fileName);

		CRenderable::SMaterial Material;
    };

    std::vector<SMeshBuffer *> MeshBuffers;

    CMesh();
    ~CMesh();

	static CMesh * Load(std::string const & FileName);

    uint const getVertexCount() const;

    void centerMeshByAverage(vec3f const & CenterLocation);
    void centerMeshByExtents(vec3f const & CenterLocation);

    void resizeMesh(vec3f const & Scale);

    vec3f const getExtent() const;

	void reverseFaces();
    void calculateNormalsPerFace();
    void calculateNormalsPerVertex(bool CombineNear = true, float const NearTolerance = 0.01f);
	void calculateTextureCoordinates(vec3f const & uVec, vec3f const & vVec, vec2f const & Scale = vec2f(1.f));

    void updateBuffers();

    SBoundingBox3f const getBoundingBox() const;

    void linearizeIndices();

	bool const isDirty() const;
	void setDirty(bool const dirty);

	unsigned int const getRevision() const;

};
